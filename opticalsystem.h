#ifndef OPTICALSYSTEM_H
#define OPTICALSYSTEM_H

#include <QGraphicsScene>

class Reflector;
class LightSource;

class OpticalSystem : public QGraphicsScene
{
    Q_OBJECT
public:
    OpticalSystem(qreal x, qreal y, qreal width, qreal height, QObject *parent = 0);
    void addReflector(Reflector *reflector);
    void addLightSource(LightSource *lightSource);
    inline QList<Reflector *> const &reflectors();
    inline QList<LightSource *> const &lightSources();
private:
    QList<Reflector *> m_reflectors;
    QList<LightSource *> m_lightSources;
signals:

public slots:

};

QList<Reflector *> const &OpticalSystem::reflectors()
{
    return m_reflectors;
}

QList<LightSource *> const &OpticalSystem::lightSources()
{
    return m_lightSources;
}

#endif // OPTICALSYSTEM_H
