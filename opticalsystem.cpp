#include "opticalsystem.h"
#include "absorber.h"
#include "settings.h"
#include "reflector.h"
#include "lightsource.h"

OpticalSystem::OpticalSystem(qreal x, qreal y, qreal width, qreal height, QObject *parent) :
    QGraphicsScene(x, y, width, height, parent)
{
    setBackgroundBrush(QBrush(Qt::lightGray));
    m_reflectors.append(new Absorber(Settings::minX, Settings::minY, Settings::minX, Settings::maxY));
    m_reflectors.append(new Absorber(Settings::minX, Settings::maxY, Settings::maxX, Settings::maxY));
    m_reflectors.append(new Absorber(Settings::maxX, Settings::maxY, Settings::maxX, Settings::minY));
    m_reflectors.append(new Absorber(Settings::maxX, Settings::minY, Settings::minX, Settings::minY));
}

void OpticalSystem::addReflector(Reflector *reflector)
{
    addItem(reflector);
    m_reflectors.append(reflector);
}

void OpticalSystem::addLightSource(LightSource *lightSource)
{
    addItem(lightSource);
    m_lightSources.append(lightSource);
}
