#include "absorber.h"

#include "label.h"
#include "normal.h"
#include "opticalsystem.h"
#include "ray.h"
#include "settings.h"

Absorber::Absorber(qreal x1, qreal y1, qreal x2, qreal y2, OpticalSystem * opticalSystem, QGraphicsItem * parent) :
    Reflector(opticalSystem, parent)
{
    setFlag(QGraphicsItem::ItemHasNoContents, true);
    m_leftEdge = QPointF(x1, y1);
    m_rightEdge = QPointF(x2, y2);
}

Absorber::~Absorber()
{
}

int Absorber::type() const
{
    return OpticalDevice::Absorber;
}

QPointF Absorber::leftEdge() const
{
    return m_leftEdge;
}

QPointF Absorber::rightEdge() const
{
    return m_rightEdge;
}

qreal Absorber::scalar(const Ray * ray) const
{
    QLineF vector = ray->line();
    qreal rx = vector.x1(); //x coordinate of ray starting point
    qreal ry = vector.y1(); //y coordinate of ray starting point
    qreal rdx = vector.dx(); //horizontal component of the ray's vector
    qreal rdy = vector.dy(); //vertical component of the ray's vector
    //calculate on which side of a ray do the absorber's vertices lie
    qreal l = rdy * (m_leftEdge.x() - rx) - rdx * (m_leftEdge.y() - ry);
    qreal r = rdy * (m_rightEdge.x() - rx) - rdx * (m_rightEdge.y() - ry);
    //both points lie on the same side of ray - intersection impossible
    if((Settings::fuzzyIsGreaterThanZero(l) && Settings::fuzzyIsGreaterThanZero(r)) || (Settings::fuzzyIsLessThanZero(l) && Settings::fuzzyIsLessThanZero(r))) return -1.0;
    qreal mx = m_leftEdge.x(); //x coordinate of mirror segment edge
    qreal my = m_leftEdge.y(); //y coordinate of mirror segment edge
    qreal mdx = m_rightEdge.x() - mx; //horizontal component of the mirror segment's vector
    qreal mdy = m_rightEdge.y() - my; //vertical component of the mirror segment's vector
    //plug: (x = rx + d * rdx) and (y = ry + d * rdy) into line equation: (mdy * (x - mx) - mdx * (y - my) = 0) and solve for d
    return (mdx * ry - mdy * rx + mdy * mx - mdx * my) / (mdy * rdx - mdx * rdy);
}

void Absorber::reflect(Ray *) const
{
    return; //absorber never reflects
}
