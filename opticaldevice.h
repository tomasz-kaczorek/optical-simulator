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
    enum
    {
        Absorber = UserType,
        PlaneMirror = UserType + 1,
        ConcaveMirror = UserType + 2,
        DiffractionGrating = UserType + 3,
        Slit = UserType + 4,
        PointSource = UserType + 5
    };

    virtual int type() const = 0;

    OpticalSystem * system();

    void addLabel();
    void showLabel();
    void hideLabel();
    void newLabelPen();

    void addNormal();
    void showNormal();
    void hideNormal();
    void newNormalPen();

    void newPen();

    QString name() const;
    void setName(QString name);

    QList<Reflector *> const & reflectors();
    QList<LightSource *> const & lightSources();
protected:
    OpticalSystem * m_opticalSystem;
    Label * m_label;
    Normal * m_normal;
    QPen m_pen;
    QPainterPath m_path;
public: //QGraphicsItem
    void setRotation(qreal angle);
protected: //QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);

};

#endif // OPTICALDEVICE_H
