#include "pointsource.h"

#include "label.h"
#include "opticalsystem.h"
#include "ray.h"

#include <QGraphicsScene>
#include <qmath.h>

PointSource::PointSource(QString name, qreal x, qreal y, qreal beginAngle, qreal endAngle, int quantity, qreal wavelength, Orders orders, bool active, OpticalSystem * opticalSystem, QGraphicsItem *parent) :
    LightSource(opticalSystem, parent),
    m_beginAngle(beginAngle),
    m_endAngle(endAngle),
    m_quantity(quantity),
    m_wavelength(wavelength),
    m_orders(orders),
    m_active(active)
{
    prepareGeometryChange();
    addLabel();
    setName(name);
    setX(x);
    setY(y);
    setRotation(-90);
    m_path.moveTo(-5.0, 0.0);
    m_path.lineTo(5.0, 0.0);
    m_path.moveTo(0.0, -5.0);
    m_path.lineTo(0.0, 5.0);
    m_color = RGB();
    build();
}

PointSource::~PointSource()
{
    qDeleteAll(m_rays);
}

qreal PointSource::beginAngle() const
{
    return m_beginAngle;
}

void PointSource::setBeginAngle(qreal beginAngle)
{
    m_beginAngle = beginAngle;
}

qreal PointSource::endAngle() const
{
    return m_endAngle;
}

void PointSource::setEndAngle(qreal endAngle)
{
    m_endAngle = endAngle;
}

int PointSource::quantity() const
{
    return m_quantity;
}

void PointSource::setQuantity(int quantity)
{
    m_quantity = quantity;
}

void PointSource::setWavelength(qreal wavelength)
{
    m_wavelength = wavelength;
    m_color = RGB();
}

bool PointSource::order(Orders::Order order) const
{
    return m_orders[order];
}

void PointSource::setOrder(Orders::Order order, bool visible)
{
    m_orders.set(order, visible);
}

bool PointSource::active() const
{
    return m_active;
}

void PointSource::setActive(bool active)
{
    m_active = active;
}

void PointSource::build(bool color)
{
    prepareGeometryChange();
    if(color)
    {
        if(m_active)
        {
            foreach(Ray * ray, m_rays) ray->replot(m_wavelength, m_color, m_orders);
        }
    }
    else
    {
        qDeleteAll(m_rays);
        m_rays.clear();
        if(m_active)
        {
            if(m_quantity == 1) addRay(m_beginAngle);
            else
            {
                qreal spanAngle = (m_endAngle - m_beginAngle) > 0.0 ? m_endAngle - m_beginAngle : 360.0 + m_endAngle - m_beginAngle;
                for(int i = 0; i < m_quantity; ++i) addRay(m_beginAngle + spanAngle * i / (m_quantity - 1));
            }
            foreach(Ray * ray, m_rays) ray->plot();
        }
    }
}

QColor PointSource::RGB()
{
    double t;
    double R = 0.0;
    double G = 0.0;
    double B = 0.0;
    if((m_wavelength >= 400.0) && (m_wavelength < 410.0))
    {
        t = (m_wavelength - 400.0) / (410.0 - 400.0);
        R = (0.28 * t) - (0.14 * t * t);
    }
    else if((m_wavelength >= 410.0) && (m_wavelength < 475.0))
    {
        t = (m_wavelength - 410.0) / (475.0 - 410.0);
        R = 0.14 - (0.14 * t * t);
    }
    else if((m_wavelength >= 545.0) && (m_wavelength < 595.0))
    {
        t = (m_wavelength - 545.0) / (595.0 - 545.0);
        R = (1.98 * t) - (t * t);
    }
    else if((m_wavelength >= 595.0) && (m_wavelength < 650.0))
    {
        t = (m_wavelength - 595.0) / (650.0 - 595.0);
        R = 0.98 + (0.06 * t)-(0.40 * t * t);
    }
    else if((m_wavelength >= 650.0) && (m_wavelength < 700.0))
    {
        t = (m_wavelength - 650.0) / (700.0 - 650.0);
        R = 0.64 - (0.84 * t) + (0.20 * t * t);
    }
    if((m_wavelength >= 415.0) && (m_wavelength < 475.0))
    {
        t = (m_wavelength - 415.0) / (475.0 - 415.0);
        G = (0.80 * t * t);
    }
    else if((m_wavelength >= 475.0) && (m_wavelength < 590.0))
    {
        t = (m_wavelength - 475.0) / (590.0 - 475.0);
        G = 0.8 + (0.76 * t) - (0.80 * t * t);
    }
    else if((m_wavelength >= 585.0) && (m_wavelength < 639.0))
    {
        t = (m_wavelength - 585.0) / (639.0 - 585.0);
        G = 0.84 - (0.84 * t);
    }
    if((m_wavelength >= 400.0) && (m_wavelength < 475.0))
    {
        t = (m_wavelength - 400.0) / (475.0 - 400.0);
        B = (2.20 * t) - (1.50 * t * t);
    }
    else if((m_wavelength >= 475.0) && (m_wavelength < 560.0))
    {
        t = (m_wavelength - 475.0) / (560.0 - 475.0);
        B = 0.7 - (t) + (0.30 * t * t);
    }
    return QColor(R * 255.0, G*255.0, B*255.0);
}

void PointSource::addRay(qreal angle)
{
    Ray * ray = new Ray(x(), y(), angle, m_wavelength, m_orders, QPen(color(), 0.0), reflectors());
    m_rays.append(ray);
    m_opticalSystem->scene()->addItem(ray);
}

qreal PointSource::wavelength() const
{
    return m_wavelength;
}

QColor PointSource::color() const
{
    return m_color;
}

void PointSource::replot(Reflector * reflector)
{
    foreach(Ray * ray, m_rays) ray->replot(reflector);
}

int PointSource::type() const
{
    return OpticalDevice::PointSource;
}
