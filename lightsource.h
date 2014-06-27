#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "opticaldevice.h"

#include <QColor>
#include <QGraphicsItem>

class Ray;

class LightSource : public OpticalDevice
{
public:
    LightSource(QGraphicsItem *parent = 0);
    ~LightSource();

    inline qreal beginAngle();
    inline void setBeginAngle(qreal beginAngle);
    inline qreal endAngle();
    inline void setEndAngle(qreal endAngle);
    inline int quantity();
    inline void setQuantity(int quantity);
    inline qreal wavelength();
    inline void setWavelength(qreal wavelength);
    inline bool *visibleOrders();
    inline bool visibleOrder(int order);
    inline void setVisibleOrder(int order, bool visible = true);
    inline bool active();
    inline void setActive(bool active = true);
    inline QColor color();
    void addRay(qreal angle);
    void geometryChanged();
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QColor wavelengthColor(qreal wavelength, qreal intensity);
    qreal m_beginAngle;
    qreal m_endAngle;
    int m_quantity;
    qreal m_wavelength;
    bool m_visibleOrders[5];
    bool m_active;
    QColor m_color;
    QList<Ray *> m_rays;
};

qreal LightSource::beginAngle()
{
    return m_beginAngle;
}

void LightSource::setBeginAngle(qreal beginAngle)
{
    m_beginAngle = beginAngle;
}

qreal LightSource::endAngle()
{
    return m_endAngle;
}

void LightSource::setEndAngle(qreal endAngle)
{
    m_endAngle = endAngle;
}

int LightSource::quantity()
{
    return m_quantity;
}

void LightSource::setQuantity(int quantity)
{
    m_quantity = quantity;
}

qreal LightSource::wavelength()
{
    return m_wavelength;
}

void LightSource::setWavelength(qreal wavelength)
{
    m_wavelength = wavelength;
    m_color = wavelengthColor(wavelength, 0.5);
}

bool *LightSource::visibleOrders()
{
    return m_visibleOrders + 2;
}

bool LightSource::visibleOrder(int order)
{
    if(order < -2 || order > 2) return false;
    return m_visibleOrders[order + 2];
}

void LightSource::setVisibleOrder(int order, bool visible)
{
    if(order < -2 || order > 2) return;
    m_visibleOrders[order + 2] = visible;
}

bool LightSource::active()
{
    return m_active;
}

void LightSource::setActive(bool active)
{
    m_active = active;
}

QColor LightSource::color()
{
    return m_color;
}

#endif // LIGHTSOURCE_H
