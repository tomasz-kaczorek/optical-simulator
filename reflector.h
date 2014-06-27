#ifndef REFLECTOR_H
#define REFLECTOR_H

#include "opticaldevice.h"

#include <QGraphicsItem>

class Ray;

class Reflector : public OpticalDevice
{
protected: //not meant to be used independently
    Reflector(QGraphicsItem *parent = 0);
    ~Reflector();
public:
    virtual QPointF leftEdge() const = 0;
    virtual QPointF rightEdge() const = 0;
    virtual void geometryChanged() = 0;
    virtual qreal multiplier(Ray const *ray) const = 0;
    virtual void reflect(Ray *ray, bool *orders) const = 0;
};

#endif // OPTICALDEVICE_H
