#ifndef DIFFRACTIONGRATING_H
#define DIFFRACTIONGRATING_H

#include "reflector.h"

class DiffractionGrating : public Reflector
{
public:
    DiffractionGrating(QString name, qreal x, qreal y, qreal angle, qreal radius, qreal blazeAngle, qreal density, OpticalSystem * opticalSystem, QGraphicsItem * parent = 0);
    ~DiffractionGrating();

    qreal radius() const;
    qreal blazeAngle() const;
    qreal density() const;
    void setGeometry(qreal x, qreal y, qreal angle, qreal radius, qreal blazeAngle, qreal density);

    void save(QXmlStreamWriter * writer) const;

    QPointF leftEdge() const;
    QPointF rightEdge() const;

    qreal scalar(Ray const * ray) const;
    void reflect(Ray * ray) const;
private:
    qreal m_radius;
    qreal m_blazeAngle;
    qreal m_density;
    QPointF m_leftEdge;
    QPointF m_rightEdge;
};

#endif // DIFFRACTIONGRATING_H
