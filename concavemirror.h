#ifndef CONCAVEMIRROR_H
#define CONCAVEMIRROR_H

#include "reflector.h"

class ConcaveMirror : public Reflector
{
public:
    ConcaveMirror(QString name, qreal x, qreal y, qreal angle, qreal radius, qreal focalLength, OpticalSystem *opticalSystem, QGraphicsItem * parent = 0);
    ~ConcaveMirror();

    qreal radius() const;
    void setRadius(qreal radius);

    qreal focalLength() const;
    void setFocalLength(qreal focalLength);

    void build();
private:
    qreal m_radius;
    qreal m_focalLength;
    qreal m_angularRadius;
    QPointF m_circleCenter;
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

#endif // CONCAVEMIRROR_H
