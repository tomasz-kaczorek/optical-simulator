#ifndef OPTICALDEVICEFORM_H
#define OPTICALDEVICEFORM_H

#include <QWidget>

class OpticalDeviceForm : public QWidget
{
    Q_OBJECT
public:
    explicit OpticalDeviceForm(QWidget *parent = 0);
    virtual ~OpticalDeviceForm();
    virtual QString name() = 0;
    virtual void apply() = 0;
    virtual void cancel() = 0;
};

#endif // OPTICALDEVICEFORM_H
