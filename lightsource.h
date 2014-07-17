#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "opticaldevice.h"

class Reflector;

class LightSource : public OpticalDevice
{
protected:
    LightSource(OpticalSystem * opticalSystem, QGraphicsItem * parent = 0);
public:
    virtual qreal wavelength() const = 0;
    virtual QColor color() const = 0;
    virtual bool order(int order) const = 0;
    virtual void plot() = 0;
    virtual void replot(bool orders[5]) = 0;
    virtual void replot(Reflector * reflector) = 0;
};

#endif // LIGHTSOURCE_H
