#include "pointsource.h"

#include "opticalsystem.h"
#include "ray.h"

#include <QGraphicsScene>

PointSource::PointSource(QString name, qreal x, qreal y, qreal beginAngle, qreal endAngle, int quantity, qreal wavelength, bool orders[5], bool active, OpticalSystem * opticalSystem, QGraphicsItem *parent) :
    LightSource(opticalSystem, parent)
{
    prepareGeometryChange();
    addLabel();
    m_path.moveTo(-5.0, 0.0);
    m_path.lineTo(5.0, 0.0);
    m_path.moveTo(0.0, -5.0);
    m_path.lineTo(0.0, 5.0);
    setName(name);
    setX(x);
    setY(y);
    m_beginAngle = beginAngle;
    m_endAngle = endAngle;
    m_quantity = quantity;
    m_wavelength = wavelength;
    for(int i = 0; i < 5; ++i) m_orders[i] = orders[i];
    if((m_active = active))
    {
        if(m_quantity == 1) addRay(m_beginAngle);
        else for (int i = 0; i < m_quantity; ++i) addRay(m_beginAngle + (m_endAngle - m_beginAngle) * i / (m_quantity - 1));
        plot();
    }
}

PointSource::~PointSource()
{
    qDeleteAll(m_rays);
}

qreal PointSource::beginAngle() const
{
    return m_beginAngle;
}

qreal PointSource::endAngle() const
{
    return m_endAngle;
}

int PointSource::quantity() const
{
    return m_quantity;
}

bool PointSource::active() const
{
    return m_active;
}

void PointSource::setGeometry(qreal x, qreal y, qreal beginAngle, qreal endAngle, int quantity, qreal wavelength, bool orders[5], bool active)
{
    if(this->x() != x || this->y() != y || m_beginAngle != beginAngle || m_endAngle != endAngle || m_quantity != quantity || m_active != active)
    {
        prepareGeometryChange();
        setX(x);
        setY(y);
        m_beginAngle = beginAngle;
        m_endAngle = endAngle;
        m_quantity = quantity;
        m_wavelength = wavelength;
        for(int i = 0; i < 5; ++i) m_orders[i] = orders[i];
        qDeleteAll(m_rays);
        m_rays.clear();
        if((m_active = active))
        {
            if(m_quantity == 1) addRay(m_beginAngle);
            else for(int i = 0; i < m_quantity; ++i) addRay(m_beginAngle + (m_endAngle - m_beginAngle) * i / (m_quantity - 1));
            plot();
        }
    }
    else
    {
        prepareGeometryChange();
        setX(x);
        setY(y);
        m_beginAngle = beginAngle;
        m_endAngle = endAngle;
        m_quantity = quantity;
        m_wavelength = wavelength;
        for(int i = 0; i < 5; ++i) m_orders[i] = orders[i];
        bool array[5] = {false, false, m_orders[2], false, false};
        if((m_active = active))
        {
            foreach(Ray * ray, m_rays) ray->replot(array);
        }
    }
}

void PointSource::addRay(qreal angle)
{
    Ray * ray = new Ray(this, x(), y(), angle);
    m_rays.append(ray);
    m_opticalSystem->scene()->addItem(ray);
}

int PointSource::type() const
{
    return OpticalDevice::PointSource;
}

qreal PointSource::wavelength() const
{
    return m_wavelength;
}

QColor PointSource::color() const
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

    return QColor(R, G, B, 255.0);
}

bool PointSource::order(int order) const
{
    return order < -2 || order > 2 ? false : m_orders[order + 2];
}

void PointSource::plot()
{
    foreach(Ray * ray, m_rays) ray->plot();
}

void PointSource::replot(bool orders[])
{
    foreach(Ray * ray, m_rays) ray->replot(orders);
}

void PointSource::replot(Reflector * reflector)
{
    foreach(Ray * ray, m_rays) ray->replot(reflector);
}
