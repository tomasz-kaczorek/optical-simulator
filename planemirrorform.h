#ifndef PLANEMIRRORFORM_H
#define PLANEMIRRORFORM_H

#include "opticaldeviceform.h"

class OpticalDeviceTabWidget;
class PlaneMirror;

class QDoubleSpinBox;
class QLineEdit;
class QPushButton;

class PlaneMirrorForm : public OpticalDeviceForm
{
public:
    explicit PlaneMirrorForm(PlaneMirror * PlaneMirror, OpticalDeviceTabWidget * parent = 0);
    ~PlaneMirrorForm();

    QString name();
private:
    void apply();
    void cancel();
    void changed();

    PlaneMirror * m_planeMirror;
    QLineEdit * m_nameLineEdit;
    QDoubleSpinBox * m_xSpinBox;
    QDoubleSpinBox * m_ySpinBox;
    QDoubleSpinBox * m_angleSpinBox;
    QDoubleSpinBox * m_radiusSpinBox;
    QPushButton * m_applyButton;
    QPushButton * m_cancelButton;
};

#endif // PLANEMIRRORFORM_H
