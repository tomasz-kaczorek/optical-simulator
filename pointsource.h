#ifndef POINTSOURCE_H
#define POINTSOURCE_H

#include "lightsource.h"

class Ray;

class PointSource : public LightSource
{
public:
    PointSource(QString name, qreal x, qreal y, qreal beginAngle, qreal endAngle, int quantity, qreal wavelength, bool orders[5], bool active, OpticalSystem * opticalSystem, QGraphicsItem * parent = 0);
    ~PointSource();

    qreal beginAngle();
    qreal endAngle();
    int quantity();
    bool active();
    void setGeometry(qreal x, qreal y, qreal beginAngle, qreal endAngle, int quantity, qreal wavelength, bool orders[5], bool active);

    void addRay(qreal angle);

    int type();

    qreal wavelength();
    QColor color();
    bool order(int order);
    void plot();
    void replot(bool orders[5]);
    void replot(Reflector * reflector);
private:
    qreal m_beginAngle;
    qreal m_endAngle;
    int m_quantity;
    qreal m_wavelength;
    QColor m_color;
    bool m_orders[5];
    bool m_active;
    QList<Ray *> m_rays;
};
#endif // POINTSOURCE_H
