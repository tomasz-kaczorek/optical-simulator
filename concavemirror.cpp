#include "concavemirror.h"

#include "label.h"
#include "ray.h"
#include "settings.h"

#include <qmath.h>
#include <QPainter>

ConcaveMirror::ConcaveMirror(qreal x, qreal y, qreal angle, qreal radius, qreal focalLength, QGraphicsItem *parent) :
    Reflector(parent),
    m_radius(radius),
    m_focalLength(focalLength),
    m_angularRadius(0.0),
    m_circleCenter{0.0, 0.0}
{
    setPos(x, y);
    setRotation(angle);
    m_left = leftEdge();
    m_right = rightEdge();
}

ConcaveMirror::ConcaveMirror(QGraphicsItem *parent) :
    Reflector(parent)
{
}

ConcaveMirror::~ConcaveMirror()
{
}

qreal ConcaveMirror::radius() const
{
    return m_radius;
}

void ConcaveMirror::setRadius(qreal radius)
{
    if(m_radius == radius) return;
    prepareGeometryChange();
    m_radius = radius;
}

qreal ConcaveMirror::focalLength() const
{
    return m_focalLength;
}

void ConcaveMirror::setFocalLength(qreal focalLength)
{
    if(m_focalLength == focalLength) return;
    prepareGeometryChange();
    m_focalLength = focalLength;
}

QPointF ConcaveMirror::leftEdge() const
{
    return mapToScene(QPointF(2 * m_focalLength * (1 - qCos(m_angularRadius)), -m_radius));
}

QPointF ConcaveMirror::rightEdge() const
{
    return mapToScene(QPointF(2 * m_focalLength * (1 - qCos(m_angularRadius)), m_radius));
}

void ConcaveMirror::geometryChanged()
{
    if(m_focalLength > 0.0) m_angularRadius = qAsin(m_radius / 2 / m_focalLength);
    else m_angularRadius = M_PI;
    m_circleCenter = circleCenter();
    m_left = leftEdge();
    m_right = rightEdge();
    m_label->geometryChanged();
}

qreal ConcaveMirror::multiplier(Ray const *ray) const
{
    QLineF vector = ray->line();
    qreal rx = vector.x1(); //x coordinate of ray starting point
    qreal ry = vector.y1(); //y coordinate of ray starting point
    qreal rdx = vector.dx(); //horizontal component of the ray's vector
    qreal rdy = vector.dy(); //vertical component of the ray's vector
    //(cx, cy) is a vector from circle center to the ray start
    qreal cx = rx - m_circleCenter.x();
    qreal cy = ry - m_circleCenter.y();
    //plug: (x = rx + d * rdx) and (y = ry + d * rdy) into circle equation: (x - m_circleCenter.x()) ^ 2 + (y - m_circleCenter.y()) ^ 2 = (2 * m_focalLength) ^ 2 and solve for d
    qreal a = rdx * rdx + rdy * rdy;
    qreal b = 2 * (cx * rdx + cy * rdy);
    qreal c = cx * cx + cy * cy - 4.0 * m_focalLength * m_focalLength;
    qreal discriminant = b * b - 4.0 * a * c;
    //if discriminant < 0 there is no intersection
    //if discriminant = 0 the ray is tangential to mirror and they do not interact
    if(Settings::lessThanOrEqualZero(discriminant)) return -1.0;
    discriminant = qSqrt(discriminant);
    double d1 = (-b - discriminant) / (2.0 * a);
    double d2 = (-b + discriminant) / (2.0 * a);
    //check which solution lies on mirror
    qreal mx = m_right.x(); //x coordinate of mirror segment edge
    qreal my = m_right.y(); //y coordinate of mirror segment edge
    qreal mdx = m_left.x() - mx; //horizontal component of the line between mirror's edges
    qreal mdy = m_left.y() - my; //vertical component of the line between mirror's edges
    //calculate on which side of the line between mirror's edges do the intersection point lie
    //d1 is always smaller - check it first and return if it is valid
    if(Settings::greaterThanZero(d1) && Settings::greaterThanOrEqualZero(mdy * (rx + d1 * rdx - mx) - mdx * (ry + d1 * rdy - my))) return d1;
    if(Settings::greaterThanZero(d2) && Settings::greaterThanOrEqualZero(mdy * (rx + d2 * rdx - mx) - mdx * (ry + d2 * rdy - my))) return d2;
    //neither intersection point lies on mirror
    return -1.0;
}

void ConcaveMirror::reflect(Ray *ray, bool *orders) const
{
    if(!orders[0]) return;
    QLineF vector = ray->line();
    qreal rx = vector.x1(); //x coordinate of ray starting point
    qreal ry = vector.y1(); //y coordinate of ray starting point
    qreal mx = vector.x2(); //x coordinate of ray-mirror intersection point
    qreal my = vector.y2(); //y coordinate of ray-mirror intersection point
    qreal mdx = m_circleCenter.x() - mx; //horizontal component of the vector perpedicular to mirror's surface at intersection point
    qreal mdy = m_circleCenter.y() - my; //vertical component of the vector perpedicular to mirror's surface at intersection point
    //calculate on which side of a mirror does the ray begin
    //if it begins on the back side, return as there will be no reflection
    //vector (mdy, -mdx) is perpedicular to (mdx, mdy) and parallel to mirror's surface at intersection point
    if(Settings::greaterThanOrEqualZero(-mdx * (rx - mx) - mdy * (ry - my))) return;
    //plug: (x = mx + d * mdx) and (y = my + d * mdy) into distance equation between (rx, ry) and (x, y): sqrt((x - rx) ^ 2 + (y - ry) ^ 2)
    //abandon the root (as it is irrelevant) and minimize result to find projection of (rx, ry) on line perpedicular to mirror's surface
    //parabola's tip is located at d = -b / 2 * a
    qreal d = (mdx * (rx - mx) + mdy * (ry - my)) / (mdx * mdx + mdy * mdy);
    //reflection ray's heading is located twice as far from (rx, ry) as (x, y)
    ray->append(2 * (mx + d * mdx) - rx, 2 * (my + d * mdy) - ry);
}

QRectF ConcaveMirror::boundingRect() const
{
    qreal width = 2 * m_focalLength * (1 - qCos(m_angularRadius));
    if(width < Settings::itemNormalLength) width = Settings::itemNormalLength;
    return QRectF(-Settings::itemPenWidth, -m_radius - Settings::itemPenWidth / 2, width + Settings::itemPenWidth , 2 * m_radius + Settings::itemPenWidth);
}

QPainterPath ConcaveMirror::shape() const
{
    QPainterPath path;
    path.arcMoveTo(0.0, -2 * m_focalLength, 2 * 2 * m_focalLength, 2 * 2 * m_focalLength, 180 * (1 - m_angularRadius / M_PI ));
    path.arcTo(0.0, -2 * m_focalLength, 2 * 2 * m_focalLength, 2 * 2 * m_focalLength, 180 * (1 - m_angularRadius / M_PI ), 2 * 180 * m_angularRadius / M_PI);
    QPainterPathStroker stroker;
    stroker.setCapStyle(Qt::RoundCap);
    stroker.setJoinStyle(Qt::RoundJoin);
    stroker.setWidth(Settings::outlineWidth);
    return stroker.createStroke(path);
}

void ConcaveMirror::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(QColor(Qt::gray), 0.0));
    painter->drawLine(0.0, 0.0, Settings::itemNormalLength, 0.0);
    painter->setPen(QPen(QColor(Qt::black), Settings::itemPenWidth, Qt::SolidLine, Qt::RoundCap));
    painter->drawArc(0.0, -2 * m_focalLength, 2 * 2 * m_focalLength, 2 * 2 * m_focalLength, 16 * 180 * (1 - m_angularRadius / M_PI ), 2 * 16 * 180 * m_angularRadius / M_PI);
}

QPointF ConcaveMirror::circleCenter()
{
    return mapToScene(QPointF(2 * m_focalLength, 0.0));
}
