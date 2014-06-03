#ifndef DIFFRACTIONGRATING_H
#define DIFFRACTIONGRATING_H

#include "reflector.h"

class DiffractionGrating : public Reflector
{
public:
    DiffractionGrating(QGraphicsItem *parent = 0);
    ~DiffractionGrating();
    qreal radius() const;
    void setRadius(qreal radius);
    qreal blazingAngle() const;
    void setBlazingAngle(qreal blazingAngle);
    qreal density() const;
    void setDensity(qreal density);
    QPointF leftEdge() const;
    QPointF rightEdge() const;
    qreal intersectionDistance(Ray const *ray) const;
    void reflectionVector(Ray *ray, QList<Ray *> *rays) const;
protected:
    QVariant itemChange (GraphicsItemChange change, QVariant const &value);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    qreal m_radius;
    qreal m_blazingAngle;
    qreal m_density;
    QPointF m_left;
    QPointF m_right;
};

#endif // DIFFRACTIONGRATING_H
