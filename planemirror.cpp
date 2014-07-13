#include "planemirror.h"

#include "label.h"
#include "opticalsystem.h"
#include "ray.h"
#include "settings.h"

#include <QPainter>
#include <QPainterPath>
#include <QPainterPathStroker>

PlaneMirror::PlaneMirror(QString name, qreal x, qreal y, qreal angle, qreal radius, OpticalSystem * opticalSystem, QGraphicsItem * parent) :
    Reflector(opticalSystem, parent)
{
    prepareGeometryChange();
    addLabel();
    addNormal();
    setName(name);
    setX(x);
    setY(y);
    setRotation(angle);
    m_radius = radius;
    m_leftEdge = leftEdge();
    m_rightEdge = rightEdge();
    m_path = QPainterPath(QPointF(m_radius, 0.0));
    m_path.lineTo(QPointF(-m_radius, 0.0));
    m_label->setRotation(rotation());
    foreach(LightSource * lightSource, m_opticalSystem->lightSources()) lightSource->replot(this);
}

PlaneMirror::~PlaneMirror()
{
    foreach(Ray * ray, m_rays) ray->plot();
}

qreal PlaneMirror::radius()  const
{
    return m_radius;
}

void PlaneMirror::setGeometry(qreal x, qreal y, qreal angle, qreal radius)
{
    if(this->x() != x || this->y() != y || rotation() != angle || m_radius != radius)
    {
        prepareGeometryChange();
        setX(x);
        setY(y);
        setRotation(angle);
        m_radius = radius;
        m_leftEdge = leftEdge();
        m_rightEdge = rightEdge();
        m_path = QPainterPath(QPointF(m_radius, 0.0));
        m_path.lineTo(QPointF(-m_radius, 0.0));
        m_label->setRotation(rotation());
        QList<Ray *> temp;
        temp.swap(m_rays);
        foreach(Ray * ray, temp) ray->plot();
        foreach(LightSource * lightSource, m_opticalSystem->lightSources()) lightSource->replot(this);
    }
}

QPointF PlaneMirror::leftEdge() const
{
    return mapToScene(QPointF(-m_radius, 0.0));
}

QPointF PlaneMirror::rightEdge() const
{
    return mapToScene(QPointF(m_radius, 0.0));
}

qreal PlaneMirror::scalar(Ray const * ray) const
{
    QLineF vector = ray->line();
    qreal rx = vector.x1(); //x coordinate of ray starting point
    qreal ry = vector.y1(); //y coordinate of ray starting point
    qreal rdx = vector.dx(); //horizontal component of the ray's vector
    qreal rdy = vector.dy(); //vertical component of the ray's vector
    //calculate on which side of a ray do the mirror's edges lie
    qreal l = rdy * (m_leftEdge.x() - rx) - rdx * (m_leftEdge.y() - ry);
    qreal r = rdy * (m_rightEdge.x() - rx) - rdx * (m_rightEdge.y() - ry);
    //both points lie on the same side of ray - intersection impossible
    if((Settings::greaterThanZero(l) && Settings::greaterThanZero(r)) || (Settings::lessThanZero(l) && Settings::lessThanZero(r))) return -1.0;
    qreal mx = m_leftEdge.x(); //x coordinate of mirror segment edge
    qreal my = m_leftEdge.y(); //y coordinate of mirror segment edge
    qreal mdx = m_rightEdge.x() - mx; //horizontal component of the mirror segment's vector
    qreal mdy = m_rightEdge.y() - my; //vertical component of the mirror segment's vector
    //plug: (x = rx + d * rdx) and (y = ry + d * rdy) into line equation: (mdy * (x - mx) - mdx * (y - my) = 0) and solve for d
    return (mdx * ry - mdy * rx + mdy * mx - mdx * my) / (mdy * rdx - mdx * rdy);
}

void PlaneMirror::reflect(Ray * ray) const
{
    QLineF vector = ray->line();
    qreal rx = vector.x1(); //x coordinate of ray starting point
    qreal ry = vector.y1(); //y coordinate of ray starting point
    qreal mx = vector.x2(); //x coordinate of ray-mirror intersection point
    qreal my = vector.y2(); //y coordinate of ray-mirror intersection point
    qreal mdx = m_leftEdge.x() - mx; //horizontal component of the line between mirror's edges
    qreal mdy = m_leftEdge.y() - my; //vertical component of the line between mirror's edges
    //calculate on which side of a mirror does the ray begin
    //if it begins on the back side, return as there will be no reflection
    if(Settings::greaterThanOrEqualZero(mdy * (rx - mx) - mdx * (ry - my))) return;
    //find a vector (mdx, mdy) perpedicular to mirror surface
    mdx = -mdy;
    mdy = m_leftEdge.x() - mx;
    //plug: (x = mx + d * mdx) and (y = my + d * mdy) into distance equation between (rx, ry) and (x, y): sqrt((x - rx) ^ 2 + (y - ry) ^ 2)
    //abandon the root (as it is irrelevant) and minimize result to find projection of (rx, ry) on line perpedicular to mirror's surface
    //parabola's tip is located at d = -b / 2 * a
    qreal d = (mdx * (rx - mx) + mdy * (ry - my)) / (mdx * mdx + mdy * mdy);
    //reflection ray's heading is located twice as far from (rx, ry) as (x, y)
    //(result) = (x, y) + ((x, y) - (rx, ry)) = 2 * (x, y) - (rx, ry)
    ray->append(2.0 * (mx + d * mdx) - rx, 2.0 * (my + d * mdy) - ry);
}

