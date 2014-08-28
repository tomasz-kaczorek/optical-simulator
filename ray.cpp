#include "ray.h"

#include "lightsource.h"
#include "opticalsystem.h"
#include "reflector.h"
#include "settings.h"

#include <float.h>

Ray::Ray(qreal x, qreal y, qreal angle, qreal wavelength, const Orders & orders, const QPen & pen, QList<Reflector *> const & reflectors, QGraphicsItem * parent) :
    QGraphicsLineItem(x, y, x + 1, y, parent),
    m_recursionDepth(0),
    m_wavelength(wavelength),
    m_orders(orders),
    m_reflector(nullptr),
    m_reflectors(reflectors)
{
    QLineF l = line();
    l.setAngle(angle);
    setLine(l);
    setPen(pen);
    for(int i = 0; i < Orders::Size; ++i) m_rays[i] = nullptr;
}

Ray::Ray(unsigned int recursionDepth, qreal x1, qreal y1, qreal x2, qreal y2, qreal wavelength, const Orders & orders, const QPen & pen, QList<Reflector *> const & reflectors, QGraphicsItem * parent) :
    QGraphicsLineItem(x1, y1, x2, y2, parent),
    m_recursionDepth(recursionDepth),
    m_wavelength(wavelength),
    m_orders(orders),
    m_reflector(nullptr),
    m_reflectors(reflectors)
{
    setPen(pen);
    for(int i = 0; i < Orders::Size; ++i) m_rays[i] = nullptr;
}

Ray::~Ray()
{
    if(m_reflector) m_reflector->removeRay(this);
}

qreal Ray::wavelength() const
{
    return m_wavelength;
}

bool Ray::order(Orders::Order order) const
{
    return m_orders[order] && !m_rays[order];
}

void Ray::append(qreal x, qreal y)
{
    if(m_recursionDepth < Settings::allowedRecursionDepth)
    {
        m_rays[Orders::Zero] = new Ray(m_recursionDepth + 1, line().x2(), line().y2(), x, y, m_wavelength, m_orders, pen(), m_reflectors, this);
        m_rays[Orders::Zero]->plot();
    }
}

void Ray::append(qreal x, qreal y, Orders::Order order)
{
    switch(order)
    {
        case Orders::SecondNegative:
            m_rays[Orders::SecondNegative] = new Ray(m_recursionDepth + 1, line().x2(), line().y2(), x, y, m_wavelength, m_orders, QPen(pen().brush(), 0.0, Qt::DotLine), m_reflectors, this);
            m_rays[Orders::SecondNegative]->plot();
            return;
        case Orders::FirstNegative:
            m_rays[Orders::FirstNegative] = new Ray(m_recursionDepth + 1, line().x2(), line().y2(), x, y, m_wavelength, m_orders, QPen(pen().brush(), 0.0, Qt::DashLine), m_reflectors, this);
            m_rays[Orders::FirstNegative]->plot();
            return;
        case Orders::Zero:
            m_rays[Orders::Zero] = new Ray(m_recursionDepth + 1, line().x2(), line().y2(), x, y, m_wavelength, m_orders, QPen(pen().brush(), 0.0, Qt::SolidLine), m_reflectors, this);
            m_rays[Orders::Zero]->plot();
            return;
        case Orders::FirstPositive:
            m_rays[Orders::FirstPositive] = new Ray(m_recursionDepth + 1, line().x2(), line().y2(), x, y, m_wavelength, m_orders, QPen(pen().brush(), 0.0, Qt::DashLine), m_reflectors, this);
            m_rays[Orders::FirstPositive]->plot();
            return;
        case Orders::SecondPositive:
            m_rays[Orders::SecondPositive] = new Ray(m_recursionDepth + 1, line().x2(), line().y2(), x, y, m_wavelength, m_orders, QPen(pen().brush(), 0.0, Qt::DotLine), m_reflectors, this);
            m_rays[Orders::SecondPositive]->plot();
            return;
        case Orders::Max:
            m_rays[Orders::Max] = new Ray(m_recursionDepth + 1, line().x2(), line().y2(), x, y, m_wavelength, m_orders, QPen(pen().brush(), 0.0, Qt::SolidLine), m_reflectors, this);
            m_rays[Orders::Max]->plot();
            return;
        default:
            return;
    }
}

void Ray::adjust(qreal adjustment)
{
    QLineF l = line();
    l.setLength(l.length() * adjustment);
    setLine(l);
}

void Ray::remove(int i)
{
    delete m_rays[i];
    m_rays[i] = nullptr;
}

void Ray::removeAll()
{
    for(int i = 0; i < Orders::Size; ++i)
    {
        delete m_rays[i];
        m_rays[i] = nullptr;
    }
}

void Ray::plot()
{
    removeAll();
    m_reflector = nullptr;
    qreal adjustment;
    qreal bestAdjustment = DBL_MAX;
    foreach(Reflector * reflector, m_reflectors)
    {
        adjustment = reflector->scalar(this);
        if(Settings::fuzzyIsGreaterThanZero(adjustment) && adjustment < bestAdjustment)
        {
            bestAdjustment = adjustment;
            m_reflector = reflector;
        }
    }
    adjust(bestAdjustment);
    m_reflector->addRay(this);
    m_reflector->reflect(this);
}

void Ray::replot(Orders orders)
{
    for(int i = 0; i < Orders::Size; ++i)
    {
        if(orders[i])
        {
            remove(i);
        }
        else if(m_rays[i])
        {
            if(m_orders[i]) m_rays[i]->replot(m_wavelength, pen().color(), m_orders);
            else remove(i);
        }
    }
    m_reflector->reflect(this);
}

void Ray::replot(qreal wavelength, QColor color, Orders orders)
{
    prepareGeometryChange();
    QPen p = pen();
    p.setColor(color);
    setPen(p);
    m_wavelength = wavelength;
    m_orders = orders;
    replot(Orders::SecondNegative | Orders::FirstNegative | Orders::FirstPositive | Orders::SecondPositive);
}

void Ray::replot(Reflector * reflector)
{
    qreal adjustment = reflector->scalar(this);
    if(adjustment > 0.0 && adjustment < 1.0)
    {
        adjust(adjustment);
        if(m_reflector) m_reflector->removeRay(this);
        removeAll();
        m_reflector = reflector;
        m_reflector->addRay(this);
        m_reflector->reflect(this);
    }
    else
    {
        for(int i = 0; i < Orders::Size; ++i) if(m_rays[i]) m_rays[i]->replot(reflector);
    }
}

void Ray::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setCompositionMode(QPainter::CompositionMode_Plus);
    QGraphicsLineItem::paint(painter, option, widget);
}
