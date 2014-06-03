#include "absorber.h"
#include "settings.h"
#include "ray.h"

Absorber::Absorber(qreal x1, qreal y1, qreal x2, qreal y2)
{
    setFlag(QGraphicsItem::ItemHasNoContents, true);
    m_left = QPointF(x1, y1);
    m_right = QPointF(x2, y2);
}

QPointF Absorber::leftEdge() const
{
    return QPointF(0.0, 0.0);
}

QPointF Absorber::rightEdge() const
{
    return QPointF(0.0, 0.0);
}

qreal Absorber::intersectionDistance(const Ray *ray) const
{
    qreal rx = ray->x1(); //x coordinate of ray starting point
    qreal ry = ray->y1(); //y coordinate of ray starting point
    qreal rdx = ray->dx(); //horizontal component of the ray's vector
    qreal rdy = ray->dy(); //vertical component of the ray's vector
    //calculate on which side of a ray do the absorber's vertices lie
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

void Absorber::reflectionVector(Ray *, QList<Ray *> *) const
{
    return; //absorber never reflects
}

QRectF Absorber::boundingRect() const
{
    return QRectF(0.0, 0.0, 0.0, 0.0);
}

void Absorber::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    return;
}
