#ifndef OPTICALDEVICEFORM_H
#define OPTICALDEVICEFORM_H

#include <QWidget>

class OpticalDevice;

class OpticalDeviceForm : public QWidget
{
    Q_OBJECT
public:
    explicit OpticalDeviceForm(QWidget * parent = 0);
    virtual ~OpticalDeviceForm();

    virtual QString name() = 0;
private slots:
    virtual void apply() = 0;
    virtual void cancel() = 0;
    virtual void changed() = 0;
};

#endif // OPTICALDEVICEFORM_H
