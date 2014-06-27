#ifndef OPTICALDEVICE_H
#define OPTICALDEVICE_H

#include <QGraphicsItem>

class Label;
class OpticalSystem;

class OpticalDevice : public QGraphicsItem
{
protected: //not meant to be used independently
    OpticalDevice(QGraphicsItem *parent = 0);
    ~OpticalDevice();
public:
    QString name();
    void setName(QString name);
    OpticalSystem *system() const;
protected:
    Label *m_label;
};

#endif // OPTICALDEVICE_H
