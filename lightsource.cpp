#include <QPainter>
#include <QGraphicsScene>
#include "lightsource.h"
#include "reflector.h"
#include "settings.h"
#include "ray.h"

LightSource::LightSource(QGraphicsItem *parent) :
    OpticalDevice(parent)
{
}

LightSource::~LightSource()
{
}

void LightSource::addRay(qreal angle)
{
    Ray *ray = new Ray(this, x(), y(), angle);
    m_rays.append(ray);
    scene()->addItem(ray);
}

void LightSource::clearRays()
{
    for(int i = m_rays.size(); i > 0; --i)
    {
        Ray *ray = m_rays.takeFirst();
        scene()->removeItem(ray);
        delete ray;
    }
}

void LightSource::geometryChanged()
{
    clearRays();
    if(m_quantity == 1) addRay(m_beginAngle);
    else
    {
        for (int i = 0; i < m_quantity; i++)
        {
            addRay(m_beginAngle + (m_endAngle - m_beginAngle) * i / (m_quantity - 1));
        }
    }
    if(m_active) foreach(Ray *ray, m_rays) ray->plot();
}

QRectF LightSource::boundingRect() const
{
    return QRectF(-Settings::itemPenWidth / 2 - 2.5, -Settings::itemPenWidth / 2 - 2.5, Settings::itemPenWidth + 5, Settings::itemPenWidth + 5);
}

void LightSource::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(QPen(Qt::black, Settings::itemPenWidth + 5, Qt::SolidLine, Qt::RoundCap));
    painter->drawPoint(0.0, 0.0);
}

QColor LightSource::wavelengthColor(qreal wavelength, qreal intensity)
{
    qreal R, G, B;
    intensity *= 255.0;

    if (wavelength <= 780.0 && wavelength >= 645.0){
        R = wavelength > 700.0 ? intensity * (0.3 + 0.7 * (780.0 - wavelength) / 80.0) : intensity;
        G = B = 0.0;
    }
    else if (wavelength >= 580.0){
        R = intensity;
        G = intensity * (645.0 - wavelength) / 65.0;
        B = 0.0;
    }
    else if (wavelength >= 510.0){
        R = intensity * (wavelength - 510.0) / 70.0;
        G = intensity;
        B = 0.0;
    }
    else if (wavelength >= 490.0){
        R = 0.0;
        G = intensity;
        B = intensity * (510.0 - wavelength) / 20.0;
    }
    else if (wavelength >= 440.0){
        R = 0.0;
        G = intensity * (wavelength - 440.0) / 50.0;
        B = intensity;
    }
    else if (wavelength >= 380.0){
        R = B = wavelength < 420.0 ? intensity * (0.3 + 0.7 * (wavelength - 350.0) / 70.0) : intensity;
        R *= (440.0 - wavelength) / 90.0;
        G = 0.0;
    }
    else R = G = B = 0.0;

    return QColor(R, G, B);
}
