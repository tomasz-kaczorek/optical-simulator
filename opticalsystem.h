#ifndef OPTICALSYSTEM_H
#define OPTICALSYSTEM_H

#include <QGraphicsScene>

class LightSource;
class OpticalDeviceTabWidget;
class Reflector;

class OpticalSystem : public QGraphicsScene
{
    Q_OBJECT
public:
    OpticalSystem(QObject * parent = 0);
    ~OpticalSystem();

    void addPlaneMirror();
    void addConcaveMirror();
    void addDiffractionGrating();
    void removeReflector();

    void addPointSource();
    void removeLightSource();

    inline OpticalDeviceTabWidget * reflectorsTabs();
    inline OpticalDeviceTabWidget * lightSourcesTabs();

    inline QList<Reflector *> const & reflectors();
    inline QList<LightSource *> const & lightSources();
private:
    OpticalDeviceTabWidget *m_reflectorsTabs;
    OpticalDeviceTabWidget *m_lightSourcesTabs;

    QList<Reflector *> m_reflectors;
    QList<LightSource *> m_lightSources;
signals:

public slots:

};

OpticalDeviceTabWidget * OpticalSystem::reflectorsTabs()
{
    return m_reflectorsTabs;
}

OpticalDeviceTabWidget * OpticalSystem::lightSourcesTabs()
{
    return m_lightSourcesTabs;
}

QList<Reflector *> const & OpticalSystem::reflectors()
{
    return m_reflectors;
}

QList<LightSource *> const & OpticalSystem::lightSources()
{
    return m_lightSources;
}

#endif // OPTICALSYSTEM_H
