#include "planemirror.h"

#include "label.h"
#include "opticalsystem.h"
#include "ray.h"
#include "settings.h"

#include <QPainter>
#include <QPainterPath>

PlaneMirror::PlaneMirror(QString name, qreal x, qreal y, qreal angle, qreal radius, OpticalSystem * opticalSystem, QGraphicsItem * parent) :
    Reflector(opticalSystem, parent),
    m_radius(radius)
{
    prepareGeometryChange();
    addLabel();
    addNormal();
    setName(name);
    setX(x);
    setY(y);
    setRotation(angle);
    build();
}

PlaneMirror::~PlaneMirror()
{
    m_rays.append(nullptr);
    while(Ray * ray = m_rays.takeFirst()) ray->plot();
}

qreal PlaneMirror::radius()  const
{
    return m_radius;
}

void PlaneMirror::setRadius(qreal radius)
{
    m_radius = radius;
}

void PlaneMirror::build()
{
    prepareGeometryChange();
    m_label->setRotation(rotation());
    m_path = QPainterPath(QPointF(0.0, -m_radius));
    m_path.lineTo(QPointF(0.0, m_radius));
    m_leftEdge = leftEdge();
    m_rightEdge = rightEdge();
    m_rays.append(nullptr);
    while(Ray * ray = m_rays.takeFirst()) ray->plot();
    foreach(LightSource * lightSource, m_opticalSystem->lightSources()) lightSource->replot(this);
}

QPointF PlaneMirror::leftEdge() const
{
    return mapToScene(QPointF(0.0, -m_radius));
}

QPointF PlaneMirror::rightEdge() const
{
    return mapToScene(QPointF(0.0, m_radius));
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
    qreal mdx = m_leftEdge.x() - m_rightEdge.x(); //horizontal component of the line between mirror's edges
    qreal mdy = m_leftEdge.y() - m_rightEdge.y(); //vertical component of the line between mirror's edges
    //calculate on which side of a mirror does the ray begin
    //if it begins on the back side, return as there will be no reflection
    if(Settings::greaterThanOrEqualZero(mdy * (rx - mx) - mdx * (ry - my))) return;
    //find a vector (mdx, mdy) perpedicular to mirror surface
    mdx = m_rightEdge.y() - m_leftEdge.y();
    mdy = m_leftEdge.x() - m_rightEdge.x();
    //plug: (x = mx + d * mdx) and (y = my + d * mdy) into distance equation between (rx, ry) and (x, y): sqrt((x - rx) ^ 2 + (y - ry) ^ 2)
    //abandon the root (as it is irrelevant) and minimize result to find projection of (rx, ry) on line perpedicular to mirror's surface
    //parabola's tip is located at d = -b / 2 * a
    qreal d = (mdx * (rx - mx) + mdy * (ry - my)) / (mdx * mdx + mdy * mdy);
    //reflection ray's heading is located twice as far from (rx, ry) as (x, y)
    //(result) = (x, y) + ((x, y) - (rx, ry)) = 2 * (x, y) - (rx, ry)
    ray->append(2.0 * (mx + d * mdx) - rx, 2.0 * (my + d * mdy) - ry);
}

int PlaneMirror::type() const
{
    return OpticalDevice::PlaneMirror;
}
