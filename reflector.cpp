#include "reflector.h"

Reflector::Reflector(OpticalSystem * opticalSystem, QGraphicsItem * parent) :
    OpticalDevice(opticalSystem, parent)
{
}

void Reflector::addRay(Ray * ray)
{
    m_rays.append(ray);
}

void Reflector::removeRay(Ray * ray)
{
    m_rays.removeOne(ray);
}
