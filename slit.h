#ifndef SLIT_H
#define SLIT_H

#include "reflector.h"

class Slit : public Reflector
{
public:
    Slit(QString name, qreal x, qreal y, qreal angle, qreal radius, qreal slitRadius, OpticalSystem * opticalSystem, QGraphicsItem * parent = 0);
    ~Slit();

    qreal radius() const;
    void setRadius(qreal radius);

    qreal slitRadius() const;
    void setSlitRadius(qreal slitRadius);

    void build();
private:
    qreal m_radius;
    qreal m_slitRadius;
    QPointF m_leftEdge;
    QPointF m_rightEdge;
    QPointF m_leftSlitEdge;
    QPointF m_rightSlitEdge;

public: //Reflector
    QPointF leftEdge() const override;
    QPointF rightEdge() const override;

    qreal scalar(Ray const * ray) const override;
    void reflect(Ray * ray) const override;

public: //OpticalDevice
    int type() const override;
};

#endif // SLIT_H
