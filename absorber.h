#ifndef ABSORBER_H
#define ABSORBER_H

#include "reflector.h"

class Absorber : public Reflector
{
public:
    Absorber(qreal x1, qreal y1, qreal x2, qreal y2, OpticalSystem * opticalSystem, QGraphicsItem * parent = 0);
    ~Absorber();

    int type();

    QPointF leftEdge() const;
    QPointF rightEdge() const;

    qreal scalar(Ray const * ray) const;
    void reflect(Ray * ray) const;

    QRectF boundingRect() const;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
private:
    QPointF m_leftEdge;
    QPointF m_rightEdge;
};

#endif // ABSORBER_H
