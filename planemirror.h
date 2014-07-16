#ifndef PLANEMIRROR_H
#define PLANEMIRROR_H

#include "reflector.h"

class PlaneMirror : public Reflector
{
public:   
    PlaneMirror(QString name, qreal x, qreal y, qreal angle, qreal radius, OpticalSystem * opticalSystem, QGraphicsItem * parent = 0);
    ~PlaneMirror();

    qreal radius() const;
    void setGeometry(qreal x, qreal y, qreal angle, qreal radius);

    int type();

    QPointF leftEdge() const;
    QPointF rightEdge() const;

    qreal scalar(Ray const * ray) const;
    void reflect(Ray * ray) const;
private:
    qreal m_radius;
    QPointF m_leftEdge;
    QPointF m_rightEdge;
};

#endif // PLANEMIRROR_H
