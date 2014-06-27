#ifndef CONCAVEMIRROR_H
#define CONCAVEMIRROR_H

#include "reflector.h"

class ConcaveMirror : public Reflector
{
public:
    ConcaveMirror(qreal x, qreal y, qreal angle, qreal radius, qreal focalLength, QGraphicsItem *parent = 0);
    ConcaveMirror(QGraphicsItem *parent = 0);
    ~ConcaveMirror();
    qreal radius() const;
    void setRadius(qreal radius);
    qreal focalLength() const;
    void setFocalLength(qreal focalLength);
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
    QPointF circleCenter();
    qreal m_radius;
    qreal m_focalLength;
    qreal m_angularRadius;
    QPointF m_circleCenter;
    QPointF m_left;
    QPointF m_right;
};

#endif // CONCAVEMIRROR_H
