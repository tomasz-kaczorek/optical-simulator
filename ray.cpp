#include "ray.h"

#include "lightsource.h"
#include "opticalsystem.h"
#include "reflector.h"
#include "settings.h"

#include <float.h>

Ray::Ray(qreal x, qreal y, qreal angle, qreal wavelength, const Orders & orders, const QPen & pen, QList<Reflector *> const & reflectors, QGraphicsItem * parent) :
    QGraphicsItem(parent),
    m_pen(pen),
    m_line(x, y, x + 1, y),
    m_recursionDepth(0),
    m_wavelength(wavelength),
    m_orders(orders),
    m_reflector(nullptr),
    m_reflectors(reflectors)
{
    m_line.setAngle(angle);
    setZValue(m_wavelength);
    for(int i = 0; i < m_orders.size(); ++i) m_rays[i] = nullptr;
}

Ray::Ray(unsigned int recursionDepth, qreal x1, qreal y1, qreal x2, qreal y2, qreal wavelength, const Orders & orders, const QPen & pen, QList<Reflector *> const & reflectors, QGraphicsItem * parent) :
    QGraphicsItem(parent),
    m_pen(pen),
    m_line(x1, y1, x2, y2),
    m_recursionDepth(recursionDepth),
    m_wavelength(wavelength),
    m_orders(orders),
    m_reflector(nullptr),
    m_reflectors(reflectors)
{
    setZValue(m_wavelength);
    for(int i = 0; i < m_orders.size(); ++i) m_rays[i] = nullptr;
}

Ray::~Ray()
{
    if(m_reflector) m_reflector->removeRay(this);
}

QLineF Ray::line() const
{
    return m_line;
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
        m_rays[Orders::Zero] = new Ray(m_recursionDepth, m_line.x2(), m_line.y2(), x, y, m_wavelength, m_orders, m_pen, m_reflectors, this);
        m_rays[Orders::Zero]->plot();
    }
}

void Ray::append(qreal x, qreal y, Orders::Order order)
{
    switch(order)
    {
        case Orders::SecondNegative:
            m_rays[Orders::SecondNegative] = new Ray(m_recursionDepth, m_line.x2(), m_line.y2(), x, y, m_wavelength, m_orders, QPen(m_pen.brush(), 0.0, Qt::DotLine), m_reflectors, this);
            m_rays[Orders::SecondNegative]->plot();
            return;
        case Orders::FirstNegative:
            m_rays[Orders::FirstNegative] = new Ray(m_recursionDepth, m_line.x2(), m_line.y2(), x, y, m_wavelength, m_orders, QPen(m_pen.brush(), 0.0, Qt::DashLine), m_reflectors, this);
            m_rays[Orders::FirstNegative]->plot();
            return;
        case Orders::Zero:
            m_rays[Orders::Zero] = new Ray(m_recursionDepth, m_line.x2(), m_line.y2(), x, y, m_wavelength, m_orders, QPen(m_pen.brush(), 0.0, Qt::SolidLine), m_reflectors, this);
            m_rays[Orders::Zero]->plot();
            return;
        case Orders::FirstPositive:
            m_rays[Orders::FirstPositive] = new Ray(m_recursionDepth, m_line.x2(), m_line.y2(), x, y, m_wavelength, m_orders, QPen(m_pen.brush(), 0.0, Qt::DashLine), m_reflectors, this);
            m_rays[Orders::FirstPositive]->plot();
            return;
        case Orders::SecondPositive:
            m_rays[Orders::SecondPositive] = new Ray(m_recursionDepth, m_line.x2(), m_line.y2(), x, y, m_wavelength, m_orders, QPen(m_pen.brush(), 0.0, Qt::DotLine), m_reflectors, this);
            m_rays[Orders::SecondPositive]->plot();
            return;
        case Orders::Max:
            m_rays[Orders::Max] = new Ray(m_recursionDepth, m_line.x2(), m_line.y2(), x, y, m_wavelength, m_orders, QPen(m_pen.brush(), 0.0, Qt::SolidLine), m_reflectors, this);
            m_rays[Orders::Max]->plot();
            return;
    }
}

void Ray::adjust(qreal adjustment)
{
    prepareGeometryChange();
    m_line.setLength(m_line.length() * adjustment);
}

void Ray::remove(int order)
{
    delete m_rays[order];
    m_rays[order] = nullptr;
}

void Ray::plot()
{
    for(int i = 0; i < m_orders.size(); ++i)
    {
        remove(i);
    }
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

void Ray::replot()
{
    remove(Orders::SecondNegative);
    remove(Orders::FirstNegative);
    remove(Orders::FirstPositive);
    remove(Orders::SecondPositive);

    if(m_rays[Orders::Zero])
    {
        if(m_orders[Orders::Zero]) m_rays[Orders::Zero]->replot(m_wavelength, m_pen.color(), m_orders);
        else remove(Orders::Zero);
    }
    if(m_rays[Orders::Max])
    {
        if(m_orders[Orders::Max]) m_rays[Orders::Max]->replot(m_wavelength, m_pen.color(), m_orders);
        else remove(Orders::Max);
    }

    m_reflector->reflect(this);
}

void Ray::replot(qreal wavelength, QColor color, Orders orders)
{
    prepareGeometryChange();
    m_pen.setColor(color);
    m_wavelength = wavelength;
    m_orders = orders;
    setZValue(m_wavelength);
    replot();
}

void Ray::replot(Reflector * reflector)
{
    qreal adjustment = reflector->scalar(this);
    if(adjustment > 0.0 && adjustment < 1.0)
    {
        adjust(adjustment);
        if(m_reflector) m_reflector->removeRay(this);
        for(int i = 0; i < m_orders.size(); ++i)
        {
            remove(i);
        }
        m_reflector = reflector;
        m_reflector->addRay(this);
        m_reflector->reflect(this);
    }
    else
    {
        for(int i = 0; i < m_orders.size(); ++i) if(m_rays[i]) m_rays[i]->replot(reflector);
    }
}

QRectF Ray::boundingRect() const
{
    return QRectF(qMin(m_line.x1(), m_line.x2()), qMin(m_line.y1(), m_line.y2()), qAbs(m_line.dx()), qAbs(m_line.dy()));
}

void Ray::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(m_pen);
    painter->drawLine(m_line);
}
