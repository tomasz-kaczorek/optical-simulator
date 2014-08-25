#ifndef OPTICALSYSTEM_H
#define OPTICALSYSTEM_H

#include <QGraphicsView>
#include "orders.h"

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

    void newScene();

    void addPlaneMirror(QString name, qreal x, qreal y, qreal angle, qreal radius);
    void addConcaveMirror(QString name, qreal x, qreal y, qreal angle, qreal radius, qreal focalLength);
    void addDiffractionGrating(QString name, qreal x, qreal y, qreal angle, qreal radius, qreal blazeAngle, qreal density);
    void addSlit(QString name, qreal x, qreal y, qreal angle, qreal radius, qreal slitRadius);

    void addPointSource(QString name, qreal x, qreal y, qreal beginAngle, qreal endAngle, int quantity, qreal wavelength, Orders orders, bool active);

    QGraphicsScene * scene();

    OpticalDeviceTabWidget * reflectorsTabs();
    OpticalDeviceTabWidget * lightSourcesTabs();

    QList<Reflector *> const & reflectors();
    QList<LightSource *> const & lightSources();
public slots:
    void newSystem();
    void openSystem();
    void saveSystem();
    void saveSystemAs();

    void addPlaneMirror();
    void addConcaveMirror();
    void addDiffractionGrating();
    void addSlit();
    void removeReflector();

    void addPointSource();
    void removeLightSource();

    void zoom(int scale);

    void options();
private:
    QString m_filename;

    QGraphicsScene * m_scene;
    OpticalDeviceTabWidget * m_reflectorsTabs;
    OpticalDeviceTabWidget * m_lightSourcesTabs;

    QList<Reflector *> m_reflectors;
    QList<LightSource *> m_lightSources;
};

#endif // OPTICALSYSTEM_H
