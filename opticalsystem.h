#ifndef OPTICALSYSTEM_H
#define OPTICALSYSTEM_H

#include <QGraphicsView>

class LightSource;
class OpticalDeviceTabWidget;
class Reflector;

class QGraphicsScene;
class QMainWindow;
class QXmlStreamReader;
class QXmlStreamWriter;

class OpticalSystem : public QGraphicsView
{
    Q_OBJECT
public:
    OpticalSystem(QMainWindow * parent = 0);
    ~OpticalSystem();

    void open();
    void save();

    void newScene();

    void addPlaneMirror();
    void addPlaneMirror(QString name, qreal x, qreal y, qreal angle, qreal radius);
    void addConcaveMirror();
    void addConcaveMirror(QString name, qreal x, qreal y, qreal angle, qreal radius, qreal focalLength);
    void addDiffractionGrating();
    void addDiffractionGrating(QString name, qreal x, qreal y, qreal angle, qreal radius, qreal blazeAngle, qreal density);
    void removeReflector();

    void addPointSource();
    void addPointSource(QString name, qreal x, qreal y, qreal beginAngle, qreal endAngle, int quantity, qreal wavelength, bool orders[5], bool active);
    void removeLightSource();

    QGraphicsScene * scene();

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
