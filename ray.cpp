#include "ray.h"

#include "lightsource.h"
#include "opticalsystem.h"
#include "reflector.h"
#include "settings.h"

#include <float.h>

Ray::Ray(LightSource * lightSource, qreal x1, qreal y1, qreal x2, qreal y2, unsigned int recursionDepth, Qt::PenStyle style, QGraphicsItem * parent) :
    QGraphicsLineItem(x1, y1, x2, y2, parent),
    m_recursionDepth(recursionDepth),
    m_lightSource(lightSource),
    m_rays{nullptr, nullptr, nullptr, nullptr, nullptr},
    m_reflector(nullptr)
{
    setPen(QPen(QBrush(m_lightSource->color()), 0.0, style));
    setZValue(wavelength());
}

Ray::Ray(LightSource * lightSource, qreal x1, qreal y1, qreal angle, unsigned int recursionDepth, Qt::PenStyle style, QGraphicsItem * parent) :
    QGraphicsLineItem(parent),
    m_recursionDepth(recursionDepth),
    m_lightSource(lightSource),
    m_rays{nullptr, nullptr, nullptr, nullptr, nullptr},
    m_reflector(nullptr)
{
    QLineF line(x1, y1, x1 + 1.0, y1);
    line.setAngle(angle);
    setLine(line);
    setPen(QPen(QBrush(m_lightSource->color()), 0.0, style));
    setZValue(wavelength());
}

Ray::~Ray()
{
    if(m_reflector) m_reflector->removeRay(this);
}

void Ray::append(qreal x, qreal y)
{
    if(m_recursionDepth < Settings::allowedRecursionDepth)
    {
        QLineF vector = line();
        m_rays[0] = new Ray(m_lightSource, vector.x2(), vector.y2(), x, y, m_recursionDepth + 1, pen().style(), this);
        m_rays[0]->plot();
    }
}

void Ray::append(qreal x, qreal y, int order)
{
    if(m_recursionDepth < Settings::allowedRecursionDepth)
    {
        Qt::PenStyle style;
        if(order == 0) style = Qt::SolidLine;
        else if(order == -1 || order == 1) style = Qt::DashLine;
        else if(order == -2 || order == 2) style = Qt::DotLine;
        else return;
        QLineF vector = line();
        m_rays[order + 2] = new Ray(m_lightSource, vector.x2(), vector.y2(), x, y, m_recursionDepth + 1, style, this);
        m_rays[order + 2]->plot();
    }
}

void Ray::plot()
{
    for(int i = 0; i < 5; ++i)
    {
        delete m_rays[i];
        m_rays[i] = nullptr;
    }
    m_reflector = nullptr;
    qreal adjustment;
    qreal bestAdjustment = DBL_MAX;
    foreach(Reflector * reflector, m_lightSource->reflectors())
    {
        adjustment = reflector->scalar(this);
        if(Settings::greaterThanZero(adjustment) && adjustment < bestAdjustment)
        {
            bestAdjustment = adjustment;
            m_reflector = reflector;
        }
    }
    adjust(bestAdjustment);
    m_reflector->addRay(this);
    m_reflector->reflect(this);
}

void Ray::replot(bool orders[5])
{
    if(pen().color() != m_lightSource->color())
    {
        prepareGeometryChange();
        QPen newpen = pen();
        newpen.setColor(m_lightSource->color());
        setPen(newpen);
        setZValue(wavelength());
    }
    for(int i = 0; i < 5; ++i)
    {
        if(orders[i])
        {
            if(m_rays[i]) m_rays[i]->replot(orders);
        }
        else
        {
            delete m_rays[i];
            m_rays[i] = nullptr;
        }
    }
    m_reflector->reflect(this);
}

void Ray::replot(Reflector * reflector)
{
    qreal adjustment = reflector->scalar(this);
    if(adjustment > 0.0 && adjustment < 1.0)
    {
        adjust(adjustment);
        if(m_reflector) m_reflector->removeRay(this);
        for(int i = 0; i < 5; ++i)
        {
            delete m_rays[i];
            m_rays[i] = nullptr;
        }
        m_reflector = reflector;
        m_reflector->addRay(this);
        m_reflector->reflect(this);
    }
    else
    {
        for(int i = 0; i < 5; ++i) if(m_rays[i]) m_rays[i]->replot(reflector);
    }
}
