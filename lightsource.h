#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "opticaldevice.h"
#include "orders.h"

class Reflector;

class LightSource : public OpticalDevice
{
protected:
    LightSource(OpticalSystem * opticalSystem, QGraphicsItem * parent = 0);
public:
    virtual void replot(Reflector * reflector) = 0;
};

#endif // LIGHTSOURCE_H
