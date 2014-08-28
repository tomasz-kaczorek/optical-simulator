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
    qreal R, G, B;

    if (m_wavelength <= 780.0 && m_wavelength >= 645.0){
        R = m_wavelength > 700.0 ? 255.0 * (0.3 + 0.7 * (780.0 - m_wavelength) / 80.0) : 255.0;
        G = B = 0.0;
    }
    else if (m_wavelength >= 580.0){
        R = 255.0;
        G = 255.0 * (645.0 - m_wavelength) / 65.0;
        B = 0.0;
    }
    else if (m_wavelength >= 510.0){
        R = 255.0 * (m_wavelength - 510.0) / 70.0;
        G = 255.0;
        B = 0.0;
    }
    else if (m_wavelength >= 490.0){
        R = 0.0;
        G = 255.0;
        B = 255.0 * (510.0 - m_wavelength) / 20.0;
    }
    else if (m_wavelength >= 440.0){
        R = 0.0;
        G = 255.0 * (m_wavelength - 440.0) / 50.0;
        B = 255.0;
    }
    else if (m_wavelength >= 380.0){
        R = B = m_wavelength < 420.0 ? 255.0 * (0.3 + 0.7 * (m_wavelength - 350.0) / 70.0) : 255.0;
        R *= (440.0 - m_wavelength) / 90.0;
        G = 0.0;
    }
    else R = G = B = 0.0;

    return QColor(R, G, B);
}

void PointSource::addRay(qreal angle)
{
    Ray * ray = new Ray(x(), y(), angle, m_wavelength, m_orders, QPen(color()), reflectors());
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
