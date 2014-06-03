#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <QGraphicsItem>
#include <QColor>

class Ray;
class Reflector;

class LightSource : public QGraphicsItem
{
public:
    LightSource(QList<Reflector *> *reflectors, QGraphicsItem *parent = 0);
    ~LightSource();
    void plotRays();
    void setBeginAngle(qreal beginAngle);
    void setEndAngle(qreal endAngle);
    void setQuantity(int quantity);
    void setWavelength(qreal wavelength);
    void setVisibleOrders(int order, bool visible = true);
    void setActive(bool active);
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QColor wavelengthColor(qreal wavelength, qreal intensity);
    QColor m_color;
    QList<Ray *> m_rays;
    QList<Reflector *> *m_reflectors;
    qreal m_wavelength;
    int m_quantity;
    qreal m_beginAngle;
    qreal m_endAngle;
    bool m_visibleOrders[5];
    bool m_active;
};

#endif // LIGHTSOURCE_H
