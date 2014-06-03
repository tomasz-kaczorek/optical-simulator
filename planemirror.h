#ifndef PLANEMIRROR_H
#define PLANEMIRROR_H

#include "reflector.h"

class PlaneMirror : public Reflector
{
public:   
    PlaneMirror(qreal x, qreal y, qreal angle, qreal radius, QGraphicsItem *parent = 0);
    PlaneMirror(QGraphicsItem *parent = 0);
    ~PlaneMirror();
    qreal radius() const;
    void setRadius(qreal radius);
    QPointF leftEdge() const;
    QPointF rightEdge() const;
    qreal intersectionDistance(Ray const *ray) const;
    void reflectionVector(Ray *ray, QList<Ray *> *rays) const;
protected:
    QVariant itemChange(GraphicsItemChange change, QVariant const &value);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    qreal m_radius;
    QPointF m_left;
    QPointF m_right;
};

#endif // PLANEMIRROR_H
