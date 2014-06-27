#ifndef PLANEMIRROR_H
#define PLANEMIRROR_H

#include "reflector.h"

class PlaneMirror : public Reflector
{
public:   
    PlaneMirror(QGraphicsItem *parent = 0);
    ~PlaneMirror();
    qreal radius() const;
    void setRadius(qreal radius);
    QPointF leftEdge() const;
    QPointF rightEdge() const;
    void geometryChanged();
    qreal multiplier(Ray const *ray) const;
    void reflect(Ray *ray, bool *orders) const;
protected:
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    qreal m_radius;
    QPointF m_left;
    QPointF m_right;
};

#endif // PLANEMIRROR_H
