#ifndef CONCAVEMIRROR_H
#define CONCAVEMIRROR_H

#include "reflector.h"

class ConcaveMirror : public Reflector
{
public:
    ConcaveMirror(QString name, qreal x, qreal y, qreal angle, qreal radius, qreal focalLength, OpticalSystem *opticalSystem, QGraphicsItem * parent = 0);
    ~ConcaveMirror();

    qreal radius() const;
    qreal focalLength() const;
    void setGeometry(qreal x, qreal y, qreal angle, qreal radius, qreal focalLength);

    void save(QXmlStreamWriter * writer) const;

    QPointF leftEdge() const;
    QPointF rightEdge() const;

    qreal scalar(Ray const * ray) const;
    void reflect(Ray * ray) const;
private:
    qreal m_radius;
    qreal m_focalLength;
    qreal m_angularRadius;
    QPointF m_circleCenter;
    QPointF m_leftEdge;
    QPointF m_rightEdge;
};

#endif // CONCAVEMIRROR_H
