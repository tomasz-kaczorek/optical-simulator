#include "ray.h"

#include "lightsource.h"
#include "opticalsystem.h"
#include "reflector.h"
#include "settings.h"

#include <float.h>

Ray::Ray(LightSource *lightSource, qreal x1, qreal y1, qreal x2, qreal y2, unsigned int recursionDepth, int order, QGraphicsItem *parent) :
    QGraphicsLineItem(x1, y1, x2, y2, parent),
    m_recursionDepth(recursionDepth),
    m_lightSource(lightSource),
    m_reflector(nullptr),
    m_next{nullptr, nullptr, nullptr, nullptr, nullptr}
{
    if(order == 0) setPen(QPen(QBrush(m_lightSource->color()), 0.0, Qt::SolidLine));
    else if(order == -1 || order == 1) setPen(QPen(QBrush(m_lightSource->color()), 0.0, Qt::DashLine));
    else if(order == -2 || order == 2) setPen(QPen(QBrush(m_lightSource->color()), 0.0, Qt::DotLine));
}

Ray::Ray(LightSource *lightSource, qreal x1, qreal y1, qreal angle, unsigned int recursionDepth, int order, QGraphicsItem *parent) :
    QGraphicsLineItem(parent),
    m_recursionDepth(recursionDepth),
    m_lightSource(lightSource),
    m_reflector(nullptr),
    m_next{nullptr, nullptr, nullptr, nullptr, nullptr}
{
    QLineF line(x1, y1, x1 + Settings::itemNormalLength, y1);
    line.setAngle(angle);
    setLine(line);
    if(order == 0) setPen(QPen(QBrush(m_lightSource->color()), 0.0, Qt::SolidLine));
    else if(order == -1 || order == 1) setPen(QPen(QBrush(m_lightSource->color()), 0.0, Qt::DashLine));
    else if(order == -2 || order == 2) setPen(QPen(QBrush(m_lightSource->color()), 0.0, Qt::DotLine));
}

void Ray::setWavelength(qreal wavelength)
{

}

void Ray::setVisibleOrder(int order, bool visible)
{

}

void Ray::reflect(qreal x, qreal y, int order)
{
    if(m_recursionDepth >= Settings::allowedRecursionDepth || order < -2 || order > 2) return;
    QLineF vector = line();
    m_next[order + 2] = new Ray(m_lightSource, vector.x2(), vector.y2(), x, y, m_recursionDepth + 1, order, this);
    m_next[order + 2]->plot();
}

void Ray::reflect(qreal angle, int order)
{
    if(m_recursionDepth >= Settings::allowedRecursionDepth || order < -2 || order > 2) return;
    QLineF vector = line();
    m_next[order + 2] = new Ray(m_lightSource, vector.x2(), vector.y2(), angle, m_recursionDepth + 1, order, this);
    m_next[order + 2]->plot();
}

void Ray::plot()
{
    m_reflector = nullptr;
    qreal adjustment;
    qreal bestAdjustment = DBL_MAX;
    foreach(Reflector *reflector, m_lightSource->system()->reflectors())
    {
        adjustment = reflector->intersectionDistance(this);
        if(Settings::greaterThanZero(adjustment) && adjustment < bestAdjustment)
        {
            bestAdjustment = adjustment;
            m_reflector = reflector;
        }
    }
    adjust(bestAdjustment);
    m_reflector->reflectionVector(this, m_lightSource->visibleOrders());
}

void Ray::plot(Reflector *reflector)
{

}
