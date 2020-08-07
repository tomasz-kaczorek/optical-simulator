#ifndef POINTSOURCEFORM_H
#define POINTSOURCEFORM_H

#include "opticaldeviceform.h"

class OpticalDeviceTabWidget;
class PointSource;
class PreciseDoubleSpinBox;

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
private slots:
    void aim();
    void geometry();
    void color();
private:
    bool m_geometry;
    bool m_color;
    PointSource * m_pointSource;
    QLineEdit * m_nameLineEdit;
    QDoubleSpinBox * m_xSpinBox;
    QDoubleSpinBox * m_ySpinBox;
    PreciseDoubleSpinBox * m_beginAngleSpinBox;
    PreciseDoubleSpinBox * m_endAngleSpinBox;
    QSpinBox * m_quantitySpinBox;
    QDoubleSpinBox * m_wavelengthSpinBox;
    QCheckBox * m_activeCheckBox;
    QCheckBox * m_orderCheckBoxes[6];
    QPushButton * m_aimButton;
    QPushButton * m_applyButton;
    QPushButton * m_cancelButton;

public: //OpticalDeviceForm
    QString name();
private:
    void apply();
    void cancel();
    void changed();
};

#endif // POINTSOURCEFORM_H
