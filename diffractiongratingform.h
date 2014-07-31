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
    Q_OBJECT
public:
    explicit DiffractionGratingForm(DiffractionGrating * diffractionGrating, OpticalDeviceTabWidget * parent = 0);
    ~DiffractionGratingForm();
private slots:
    void geometry();
    void reflection();
private:
    bool m_geometry;
    bool m_reflection;
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

public: //OpticalDeviceForm
    QString name() override;
private:
    void apply() override;
    void cancel() override;
    void changed() override;
};

#endif // DIFFRACTIONGRATINGFORM_H
