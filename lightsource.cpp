#include <QPainter>
#include <QGraphicsScene>
#include "lightsource.h"
#include "reflector.h"
#include "settings.h"
#include "ray.h"

LightSource::LightSource(QList<Reflector *> *reflectors, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    m_reflectors(reflectors),
    m_wavelength(Settings::minWavelength),
    m_quantity(Settings::minQuantity),
    m_beginAngle(0.0),
    m_endAngle(0.0),
    m_visibleOrders{false, false, true, false, false},
    m_active(true)
{
    m_color = wavelengthColor(380.0, 0.75);
}

LightSource::~LightSource()
{
}

void LightSource::plotRays()
{
    QList<Ray *> rays(m_rays);
    Ray *ray;
    qreal distance;
    qreal bestDistance;
    Reflector *reflector;
    Reflector *bestReflector;
    while(!rays.isEmpty())
    {
        ray = rays.takeFirst();
        bestDistance = std::numeric_limits<double>::infinity();
        bestReflector = nullptr;
        for(int i = 0; i < m_reflectors->size(); i++)
        {
            reflector = m_reflectors->at(i);
            distance = reflector->intersectionDistance(ray);
            if(Settings::greaterThanZero(distance) && distance < bestDistance)
            {
                bestDistance = distance;
                bestReflector = reflector;
            }
        }
        ray->adjust(bestDistance);
        bestReflector->reflectionVector(ray, &rays);
    }
}

void LightSource::setBeginAngle(qreal beginAngle)
{
    m_beginAngle = beginAngle;
    while(!m_rays.isEmpty()) delete m_rays.takeLast();
    Ray *ray = new Ray(x(), y(), x() + 10.0, y(), m_color, Qt::SolidLine);
    ray->setAngle(m_beginAngle);
    m_rays.append(ray);
    scene()->addItem(ray);
    for (int i = 1; i < m_quantity; i++)
    {
        ray = new Ray(x(), y(), x() + 10.0, y(), m_color, Qt::SolidLine);
        ray->setAngle(m_beginAngle + (m_endAngle - m_beginAngle) * i / (m_quantity - 1));
        m_rays.append(ray);
        scene()->addItem(ray);
    }
}

void LightSource::setEndAngle(qreal endAngle)
{
    m_endAngle = endAngle;
    while(!m_rays.isEmpty()) delete m_rays.takeLast();
    Ray *ray = new Ray(x(), y(), x() + 10.0, y(), m_color, Qt::SolidLine);
    ray->setAngle(m_beginAngle);
    m_rays.append(ray);
    scene()->addItem(ray);
    for (int i = 1; i < m_quantity; i++)
    {
        ray = new Ray(x(), y(), x() + 10.0, y(), m_color, Qt::SolidLine);
        ray->setAngle(m_beginAngle + (m_endAngle - m_beginAngle) * i / (m_quantity - 1));
        m_rays.append(ray);
        scene()->addItem(ray);
    }
}

void LightSource::setQuantity(int quantity)
{
    m_quantity = quantity;
    while(!m_rays.isEmpty()) delete m_rays.takeLast();
    Ray *ray = new Ray(x(), y(), x() + 10.0, y(), m_color, Qt::SolidLine);
    ray->setAngle(m_beginAngle);
    m_rays.append(ray);
    scene()->addItem(ray);
    for (int i = 1; i < m_quantity; i++)
    {
        ray = new Ray(x(), y(), x() + 10.0, y(), m_color, Qt::SolidLine);
        ray->setAngle(m_beginAngle + (m_endAngle - m_beginAngle) * i / (m_quantity - 1));
        m_rays.append(ray);
        scene()->addItem(ray);
    }
}

void LightSource::setWavelength(qreal wavelength)
{
    m_wavelength = wavelength;
    m_color = wavelengthColor(wavelength, 0.75);
    update();
}

void LightSource::setVisibleOrders(int order, bool visible)
{
    m_visibleOrders[order + 2] = visible;
}

void LightSource::setActive(bool active)
{
    m_active = active;
}

QRectF LightSource::boundingRect() const
{
    return QRectF(-Settings::itemPenWidth / 2 - 2.5, -Settings::itemPenWidth / 2 - 2.5, Settings::itemPenWidth + 5, Settings::itemPenWidth + 5);
}

void LightSource::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(QPen(m_color, Settings::itemPenWidth + 5, Qt::SolidLine, Qt::RoundCap));
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
