#ifndef POINTSOURCE_H
#define POINTSOURCE_H

#include "lightsource.h"
#include "orders.h"

class Ray;

class PointSource : public LightSource
{
public:
    PointSource(QString name, qreal x, qreal y, qreal beginAngle, qreal endAngle, int quantity, qreal wavelength, Orders orders, bool active, OpticalSystem * opticalSystem, QGraphicsItem * parent = 0);
    ~PointSource();

    qreal beginAngle() const;
    void setBeginAngle(qreal beginAngle);

    qreal endAngle() const;
    void setEndAngle(qreal endAngle);

    int quantity() const;
    void setQuantity(int quantity);

    qreal wavelength() const;
    void setWavelength(qreal wavelength);
    QColor color() const;

    bool order(Orders::Order order) const;
    void setOrder(Orders::Order order, bool visible);

    bool active() const;
    void setActive(bool active);

    void build(bool color = false);
    QColor RGB();
private:
    void addRay(qreal angle);

    qreal m_beginAngle;
    qreal m_endAngle;
    int m_quantity;
    qreal m_wavelength;
    QColor m_color;
    Orders m_orders;
    bool m_active;
    QList<Ray *> m_rays;

public: //LightSource
    void replot(Reflector * reflector) override;
public: //OpticalDevice
    int type() const override;
};
#endif // POINTSOURCE_H
