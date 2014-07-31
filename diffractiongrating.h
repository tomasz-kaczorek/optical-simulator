#ifndef DIFFRACTIONGRATING_H
#define DIFFRACTIONGRATING_H

#include "reflector.h"

class DiffractionGrating : public Reflector
{
public:
    DiffractionGrating(QString name, qreal x, qreal y, qreal angle, qreal radius, qreal blazeAngle, qreal density, OpticalSystem * opticalSystem, QGraphicsItem * parent = 0);
    ~DiffractionGrating();

    qreal radius() const;
    void setRadius(qreal radius);

    qreal blazeAngle() const;
    void setBlazeAngle(qreal blazeAngle);

    qreal density() const;
    void setDensity(qreal density);

    void build(bool complete);
private:
    qreal m_radius;
    qreal m_blazeAngle;
    qreal m_density;
    QPointF m_leftEdge;
    QPointF m_rightEdge;

public: //Reflector
    QPointF leftEdge() const override;
    QPointF rightEdge() const override;

    qreal scalar(Ray const * ray) const override;
    void reflect(Ray * ray) const override;

public: //OpticalDevice
    int type() const override;
};

#endif // DIFFRACTIONGRATING_H
