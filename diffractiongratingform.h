#ifndef DIFFRACTIONGRATINGFORM_H
#define DIFFRACTIONGRATINGFORM_H

#include "opticaldeviceform.h"

class DiffractionGrating;
class OpticalDeviceTabWidget;

class QDoubleSpinBox;
class QLineEdit;
class QPushButton;

class DiffractionGratingForm : public OpticalDeviceForm
{
public:
    explicit DiffractionGratingForm(DiffractionGrating * diffractionGrating, OpticalDeviceTabWidget * parent = 0);
    ~DiffractionGratingForm();

    QString name();
private:
    void apply();
    void cancel();
    void changed();

    DiffractionGrating * m_diffractionGrating;
    QLineEdit * m_nameLineEdit;
    QDoubleSpinBox * m_xSpinBox;
    QDoubleSpinBox * m_ySpinBox;
    QDoubleSpinBox * m_angleSpinBox;
    QDoubleSpinBox * m_radiusSpinBox;
    QDoubleSpinBox * m_blazeAngleSpinBox;
    QDoubleSpinBox * m_densitySpinBox;
    QPushButton * m_applyButton;
    QPushButton * m_cancelButton;
};

#endif // DIFFRACTIONGRATINGFORM_H
