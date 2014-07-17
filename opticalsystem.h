#ifndef OPTICALSYSTEM_H
#define OPTICALSYSTEM_H

#include <QGraphicsView>

class LightSource;
class OpticalDeviceTabWidget;
class Reflector;

class QGraphicsScene;
class QMainWindow;

class OpticalSystem : public QGraphicsView
{
    Q_OBJECT
public:
    OpticalSystem(QMainWindow * parent = 0);
    ~OpticalSystem();

    void open();
    void save();

    void addPlaneMirror();
    void addConcaveMirror();
    void addDiffractionGrating();
    void removeReflector();

    void addPointSource();
    void removeLightSource();

    OpticalDeviceTabWidget * reflectorsTabs();
    OpticalDeviceTabWidget * lightSourcesTabs();

    QList<Reflector *> const & reflectors();
    QList<LightSource *> const & lightSources();
private:
    QGraphicsScene *m_scene;
    OpticalDeviceTabWidget *m_reflectorsTabs;
    OpticalDeviceTabWidget *m_lightSourcesTabs;

    QList<Reflector *> m_reflectors;
    QList<LightSource *> m_lightSources;
signals:

public slots:

};

#endif // OPTICALSYSTEM_H
