#include "slit.h"

#include "label.h"
#include "opticalsystem.h"
#include "ray.h"
#include "settings.h"

#include <QPainter>
#include <QPainterPath>

Slit::Slit(QString name, qreal x, qreal y, qreal angle, qreal radius, qreal slitRadius, OpticalSystem * opticalSystem, QGraphicsItem * parent) :
    Reflector(opticalSystem, parent),
    m_radius(radius),
    m_slitRadius(slitRadius)
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

Slit::~Slit()
{
    m_rays.append(nullptr);
    while(Ray * ray = m_rays.takeFirst()) ray->plot();
}

qreal Slit::radius() const
{
    return m_radius;
}

void Slit::setRadius(qreal radius)
{
    m_radius = radius;
}

qreal Slit::slitRadius() const
{
    return m_slitRadius;
}

void Slit::setSlitRadius(qreal slitRadius)
{
    m_slitRadius = slitRadius;
}

void Slit::build()
{
    prepareGeometryChange();
    m_label->setRotation(rotation());
    m_path = QPainterPath(QPointF(0.0, -m_radius));
    m_path.lineTo(0.0, -m_slitRadius);
    m_path.moveTo(0.0, m_slitRadius);
    m_path.lineTo(QPointF(0.0, m_radius));
    m_leftEdge = leftEdge();
    m_rightEdge = rightEdge();
    m_leftSlitEdge = mapToScene(QPointF(0.0, -m_slitRadius));
    m_rightSlitEdge = mapToScene(QPointF(0.0, m_slitRadius));
    m_rays.append(nullptr);
    while(Ray * ray = m_rays.takeFirst()) ray->plot();
    foreach(LightSource * lightSource, m_opticalSystem->lightSources()) lightSource->replot(this);
}

QPointF Slit::leftEdge() const
{
    return mapToScene(QPointF(0.0, -m_radius));
}

QPointF Slit::rightEdge() const
{
    return mapToScene(QPointF(0.0, m_radius));
}

qreal Slit::scalar(const Ray * ray) const
{
    QLineF vector = ray->line();
    qreal rx = vector.x1(); //x coordinate of ray starting point
    qreal ry = vector.y1(); //y coordinate of ray starting point
    qreal rdx = vector.dx(); //horizontal component of the ray's vector
    qreal rdy = vector.dy(); //vertical component of the ray's vector
    //calculate on which side of a ray do the slit's edges lie
    qreal l = rdy * (m_leftEdge.x() - rx) - rdx * (m_leftEdge.y() - ry);
    qreal r = rdy * (m_rightEdge.x() - rx) - rdx * (m_rightEdge.y() - ry);
    qreal sl = rdy * (m_leftSlitEdge.x() - rx) - rdx * (m_leftSlitEdge.y() - ry);
    qreal sr = rdy * (m_rightSlitEdge.x() - rx) - rdx * (m_rightSlitEdge.y() - ry);
    //pair of points lie on the same side of ray - intersection impossible
    if(((Settings::greaterThanZero(l) && Settings::greaterThanZero(sl)) || (Settings::lessThanZero(l) && Settings::lessThanZero(sl)))&&((Settings::greaterThanZero(r) && Settings::greaterThanZero(sr)) || (Settings::lessThanZero(r) && Settings::lessThanZero(sr)))) return -1.0;
    qreal sx = m_leftEdge.x(); //x coordinate of slit segment edge
    qreal sy = m_leftEdge.y(); //y coordinate of slit segment edge
    qreal sdx = m_rightEdge.x() - sx; //horizontal component of the slit segment's vector
    qreal sdy = m_rightEdge.y() - sy; //vertical component of the slit segment's vector
    //plug: (x = rx + d * rdx) and (y = ry + d * rdy) into line equation: (sdy * (x - sx) - sdx * (y - sy) = 0) and solve for d
    return (sdx * ry - sdy * rx + sdy * sx - sdx * sy) / (sdy * rdx - sdx * rdy);
}

void Slit::reflect(Ray *) const
{
    //slit never reflects
}

int Slit::type() const
{
    return OpticalDevice::Slit;
}
