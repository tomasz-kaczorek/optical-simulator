#include "opticalsystem.h"
#include "absorber.h"
#include "settings.h"
#include "reflector.h"
#include "lightsource.h"

OpticalSystem::OpticalSystem(qreal x, qreal y, qreal width, qreal height, QObject *parent) :
    QGraphicsScene(x, y, width, height, parent)
{
    setBackgroundBrush(QBrush(Qt::lightGray));
    m_reflectors.append(new Absorber(Settings::minX - 1.0, Settings::minY - 1.0, Settings::minX - 1.0, Settings::maxY - 1.0));
    m_reflectors.append(new Absorber(Settings::minX - 1.0, Settings::maxY + 1.0, Settings::maxX + 1.0, Settings::maxY + 1.0));
    m_reflectors.append(new Absorber(Settings::maxX + 1.0, Settings::maxY + 1.0, Settings::maxX + 1.0, Settings::minY - 1.0));
    m_reflectors.append(new Absorber(Settings::maxX + 1.0, Settings::minY - 1.0, Settings::minX - 1.0, Settings::minY - 1.0));
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
