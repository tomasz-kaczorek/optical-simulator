#include "planemirror.h"

#include "label.h"
#include "ray.h"
#include "settings.h"

#include <QPainter>
#include <QPainterPath>
#include <QPainterPathStroker>

PlaneMirror::PlaneMirror(QGraphicsItem *parent) :
    Reflector(parent)
{
}

PlaneMirror::~PlaneMirror()
{
}

qreal PlaneMirror::radius()  const
{
    return m_radius;
}

void PlaneMirror::setRadius(qreal radius)
{
    if(m_radius == radius) return
    prepareGeometryChange();
    m_radius = radius;
}

QPointF PlaneMirror::leftEdge() const
{
    return mapToScene(QPointF(0.0, -m_radius));
}

QPointF PlaneMirror::rightEdge() const
{
    return mapToScene(QPointF(0.0, m_radius));
}

void PlaneMirror::geometryChanged()
{
    m_left = leftEdge();
    m_right = rightEdge();
    m_label->geometryChanged();
}

qreal PlaneMirror::intersectionDistance(Ray const *ray) const
{
    QLineF vector = ray->line();
    qreal rx = vector.x1(); //x coordinate of ray starting point
    qreal ry = vector.y1(); //y coordinate of ray starting point
    qreal rdx = vector.dx(); //horizontal component of the ray's vector
    qreal rdy = vector.dy(); //vertical component of the ray's vector
    //calculate on which side of a ray do the mirror's edges lie
    qreal l = rdy * (m_left.x() - rx) - rdx * (m_left.y() - ry);
    qreal r = rdy * (m_right.x() - rx) - rdx * (m_right.y() - ry);
    //both points lie on the same side of ray - intersection impossible
    if((Settings::greaterThanZero(l) && Settings::greaterThanZero(r)) || (Settings::lessThanZero(l) && Settings::lessThanZero(r))) return -1.0;
    qreal mx = m_left.x(); //x coordinate of mirror segment edge
    qreal my = m_left.y(); //y coordinate of mirror segment edge
    qreal mdx = m_right.x() - mx; //horizontal component of the mirror segment's vector
    qreal mdy = m_right.y() - my; //vertical component of the mirror segment's vector
    //plug: (x = rx + d * rdx) and (y = ry + d * rdy) into line equation: (mdy * (x - mx) - mdx * (y - my) = 0) and solve for d
    return (mdx * ry - mdy * rx + mdy * mx - mdx * my) / (mdy * rdx - mdx * rdy);
}

void PlaneMirror::reflectionVector(Ray *ray, bool *orders) const
{
    if(!orders[0]) return;
    QLineF vector = ray->line();
    qreal rx = vector.x1(); //x coordinate of ray starting point
    qreal ry = vector.y1(); //y coordinate of ray starting point
    qreal mx = vector.x2(); //x coordinate of ray-mirror intersection point
    qreal my = vector.y2(); //y coordinate of ray-mirror intersection point
    qreal mdx = m_left.x() - mx; //horizontal component of the line between mirror's edges
    qreal mdy = m_left.y() - my; //vertical component of the line between mirror's edges
    //calculate on which side of a mirror does the ray begin
    //if it begins on the back side, return as there will be no reflection
    if(Settings::greaterThanOrEqualZero(mdy * (rx - mx) - mdx * (ry - my))) return;
    //find a vector (mdx, mdy) perpedicular to mirror surface
    mdx = -mdy;
    mdy = m_left.x() - mx;
    //plug: (x = mx + d * mdx) and (y = my + d * mdy) into distance equation between (rx, ry) and (x, y): sqrt((x - rx) ^ 2 + (y - ry) ^ 2)
    //abandon the root (as it is irrelevant) and minimize result to find projection of (rx, ry) on line perpedicular to mirror's surface
    //parabola's tip is located at d = -b / 2 * a
    qreal d = (mdx * (rx - mx) + mdy * (ry - my)) / (mdx * mdx + mdy * mdy);
    //reflection ray's heading is located twice as far from (rx, ry) as (x, y)
    ray->reflect(2 * (mx + d * mdx) - rx, 2 * (my + d * mdy) - ry);
}

QRectF PlaneMirror::boundingRect() const
{
    return QRectF(-Settings::itemPenWidth / 2.0, -m_radius - Settings::itemPenWidth / 2.0, Settings::itemNormalLength + Settings::itemPenWidth, 2.0 * m_radius + Settings::itemPenWidth);
}

QPainterPath PlaneMirror::shape() const
{
    QPainterPath path;
    path.moveTo(0.0, -m_radius);
    path.lineTo(0.0, m_radius);
    QPainterPathStroker stroker;
    stroker.setCapStyle(Qt::RoundCap);
    stroker.setJoinStyle(Qt::RoundJoin);
    stroker.setWidth(Settings::outlineWidth);
    return stroker.createStroke(path);
}

void PlaneMirror::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(QColor(Qt::gray), 0.0));
    painter->drawLine(0.0, 0.0, Settings::itemNormalLength, 0.0);
    painter->setPen(QPen(QColor(Qt::black), Settings::itemPenWidth, Qt::SolidLine, Qt::RoundCap));
    painter->drawLine(0.0, -m_radius, 0.0, m_radius);
}

