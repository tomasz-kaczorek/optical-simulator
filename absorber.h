#ifndef ABSORBER_H
#define ABSORBER_H

#include "reflector.h"

class Absorber : public Reflector
{
public:
    Absorber(qreal x1, qreal y1, qreal x2, qreal y2);
protected:
    QPointF leftEdge() const;
    QPointF rightEdge() const;
    void geometryChanged();
    qreal multiplier(Ray const *ray) const;
    void reflect(Ray *ray, bool *orders) const;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QPointF m_left;
    QPointF m_right;
};

#endif // ABSORBER_H
