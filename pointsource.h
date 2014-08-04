#ifndef POINTSOURCE_H
#define POINTSOURCE_H

#include "lightsource.h"

class Ray;

class PointSource : public LightSource
{
public:
    PointSource(QString name, qreal x, qreal y, qreal beginAngle, qreal endAngle, int quantity, qreal wavelength, bool orders[5], bool active, OpticalSystem * opticalSystem, QGraphicsItem * parent = 0);
    ~PointSource();

    qreal beginAngle() const;
    void setBeginAngle(qreal beginAngle);

    qreal endAngle() const;
    void setEndAngle(qreal endAngle);

    int quantity() const;
    void setQuantity(int quantity);

    void setWavelength(qreal wavelength);

    void setOrder(int order, bool visible);

    bool active() const;
    void setActive(bool active);

    void build(bool complete);
    QColor RGB();
private:
    void addRay(qreal angle);

    qreal m_beginAngle;
    qreal m_endAngle;
    int m_quantity;
    qreal m_wavelength;
    QColor m_color;
    bool m_orders[5];
    bool m_active;
    QList<Ray *> m_rays;

public: //LightSource
    qreal wavelength() const override;
    QColor color() const override;
    bool order(int order) const override;
    void plot() override;
    void replot(bool orders[5]) override;
    void replot(Reflector * reflector) override;
public: //OpticalDevice
    int type() const override;
};
#endif // POINTSOURCE_H
