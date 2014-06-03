#ifndef REFLECTOR_H
#define REFLECTOR_H

#include <QGraphicsItem>
#include <QVariant>
#include <QQueue>

class Ray;

class Reflector : public QGraphicsItem
{
public:
    Reflector(QGraphicsItem *parent = 0);
    virtual ~Reflector();

    virtual QPointF leftEdge() const = 0;
    virtual QPointF rightEdge() const = 0;
    virtual qreal intersectionDistance(Ray const *ray) const = 0;
    virtual void reflectionVector(Ray *ray, QList<Ray *> *rays) const = 0;
};

#endif // OPTICALDEVICE_H
