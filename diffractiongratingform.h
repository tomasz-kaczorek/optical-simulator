#ifndef DIFFRACTIONGRATINGFORM_H
#define DIFFRACTIONGRATINGFORM_H

#include "opticaldeviceform.h"

class DiffractionGrating;

class QDoubleSpinBox;
class QGridLayout;
class QLabel;
class QLineEdit;

class DiffractionGratingForm : public OpticalDeviceForm
{
public:
    explicit DiffractionGratingForm(DiffractionGrating *diffractionGrating, QWidget *parent = 0);
    ~DiffractionGratingForm();
    QString name();
    void apply();
    void cancel();
private:
    DiffractionGrating *m_diffractionGrating;
    QGridLayout *m_layout;
    QLabel *m_nameLabel;
    QLineEdit *m_nameLineEdit;
    QLabel *m_xLabel;
    QDoubleSpinBox *m_xSpinBox;
    QLabel *m_yLabel;
    QDoubleSpinBox *m_ySpinBox;
    QLabel *m_angleLabel;
    QDoubleSpinBox *m_angleSpinBox;
    QLabel *m_radiusLabel;
    QDoubleSpinBox *m_radiusSpinBox;
    QLabel *m_densityLabel;
    QDoubleSpinBox *m_densitySpinBox;
    QLabel *m_blazingAngleLabel;
    QDoubleSpinBox *m_blazingAngleSpinBox;
};

#endif // DIFFRACTIONGRATINGFORM_H
