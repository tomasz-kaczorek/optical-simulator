#ifndef LIGHTSOURCEFORM_H
#define LIGHTSOURCEFORM_H

#include "opticaldeviceform.h"

class LightSource;

class QCheckBox;
class QDoubleSpinBox;
class QGridLayout;
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QSpinBox;

class LightSourceForm : public OpticalDeviceForm
{
public:
    LightSourceForm(LightSource *lightSource, QWidget *parent = 0);
    ~LightSourceForm();
    QString name();
    void apply();
    void cancel();
private:
    void aim();
    LightSource *m_lightSource;
    QGridLayout *m_layout;
    QLabel *m_nameLabel;
    QLineEdit *m_nameLineEdit;
    QLabel *m_xLabel;
    QDoubleSpinBox *m_xSpinBox;
    QLabel *m_yLabel;
    QDoubleSpinBox *m_ySpinBox;
    QLabel *m_beginAngleLabel;
    QDoubleSpinBox *m_beginAngleSpinBox;
    QLabel *m_endAngleLabel;
    QDoubleSpinBox *m_endAngleSpinBox;
    QLabel *m_quantityLabel;
    QSpinBox *m_quantitySpinBox;
    QLabel *m_wavelengthLabel;
    QDoubleSpinBox *m_wavelengthSpinBox;
    QGroupBox *m_visibleOrdersGroupBox;
    QGridLayout *m_visibleOrdersLayout;
    QCheckBox *m_secondNegativeOrderCheckBox;
    QCheckBox *m_firstNegativeOrderCheckBox;
    QCheckBox *m_zeroOrderCheckBox;
    QCheckBox *m_firstPositiveOrderCheckBox;
    QCheckBox *m_secondPositiveOrderCheckBox;
    QPushButton *m_aimPushButton;
    QCheckBox *m_activeCheckBox;
};

#endif // LIGHTSOURCEFORM_H
