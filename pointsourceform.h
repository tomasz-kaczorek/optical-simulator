#ifndef POINTSOURCEFORM_H
#define POINTSOURCEFORM_H

#include "opticaldeviceform.h"

class OpticalDeviceTabWidget;
class PointSource;

class QCheckBox;
class QDoubleSpinBox;
class QLineEdit;
class QPushButton;
class QSpinBox;

class PointSourceForm : public OpticalDeviceForm
{
    Q_OBJECT
public:
    PointSourceForm(PointSource * pointSource, OpticalDeviceTabWidget * parent = 0);
    ~PointSourceForm();

    QString name();
private:
    void apply();
    void cancel();
    void changed();
private slots:
    void aim();
private:
    PointSource * m_pointSource;
    QLineEdit * m_nameLineEdit;
    QDoubleSpinBox * m_xSpinBox;
    QDoubleSpinBox * m_ySpinBox;
    QDoubleSpinBox * m_beginAngleSpinBox;
    QDoubleSpinBox * m_endAngleSpinBox;
    QSpinBox * m_quantitySpinBox;
    QDoubleSpinBox * m_wavelengthSpinBox;
    QCheckBox * m_activeCheckBox;
    QCheckBox * m_orderCheckBoxes[5];
    QPushButton * m_aimButton;
    QPushButton * m_applyButton;
    QPushButton * m_cancelButton;
};

#endif // POINTSOURCEFORM_H
