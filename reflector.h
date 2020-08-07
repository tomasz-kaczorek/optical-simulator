#ifndef REFLECTOR_H
#define REFLECTOR_H

#include "opticaldevice.h"

class LightSource;
class Ray;

class Reflector : public OpticalDevice
{
protected: //not meant to be used independently
    Reflector(OpticalSystem * opticalSystem, QGraphicsItem * parent = 0);
public:
    virtual QPointF leftEdge() const = 0;
    virtual QPointF rightEdge() const = 0;

    virtual qreal scalar(Ray const * ray) const = 0;
    virtual void reflect(Ray * ray) const = 0;

    void addRay(Ray * ray);
    void removeRay(Ray * ray);
protected:
    QList<Ray *> m_rays;
};

#endif // OPTICALDEVICE_H
