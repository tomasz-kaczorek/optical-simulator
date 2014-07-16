#ifndef OPTICALDEVICE_H
#define OPTICALDEVICE_H

#include <QGraphicsItem>

#include <QPen>

class Label;
class LightSource;
class Normal;
class OpticalSystem;
class Reflector;

class OpticalDevice : public QGraphicsItem
{
protected: //not meant to be used independently
    OpticalDevice(OpticalSystem * opticalSystem, QGraphicsItem * parent = 0);
    ~OpticalDevice();
public:
    enum { Absorber = UserType,
           PlaneMirror = UserType + 1,
           ConcaveMirror = UserType + 2,
           DiffractionGrating = UserType + 3,
           Slit = UserType + 4,
           PointSource = UserType + 5 };

    void addLabel();
    void showLabel();
    void hideLabel();

    void addNormal();
    void showNormal();
    void hideNormal();

    QString name();
    void setName(QString name);

    QList<Reflector *> const & reflectors();
    QList<LightSource *> const & lightSources();
protected:
    QRectF boundingRect() const;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);

    OpticalSystem * m_opticalSystem;
    Label * m_label;
    Normal * m_normal;
    QPen m_pen;
    QPainterPath m_path;
};

#endif // OPTICALDEVICE_H
