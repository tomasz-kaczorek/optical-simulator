#ifndef PLANEMIRROR_H
#define PLANEMIRROR_H

#include "reflector.h"

class PlaneMirror : public Reflector
{
public:
    PlaneMirror(QString name, qreal x, qreal y, qreal angle, qreal radius, OpticalSystem * opticalSystem, QGraphicsItem * parent = 0);    
    ~PlaneMirror();

    qreal radius() const;
    void setRadius(qreal radius);

    void build();
private:
    qreal m_radius;
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

#endif // PLANEMIRROR_H
