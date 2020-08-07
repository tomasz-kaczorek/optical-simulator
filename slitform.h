#ifndef SLITFORM_H
#define SLITFORM_H

#include "opticaldeviceform.h"

class OpticalDeviceTabWidget;
class Slit;

class QDoubleSpinBox;
class QLineEdit;
class QPushButton;

class SlitForm : public OpticalDeviceForm
{
    Q_OBJECT
public:
    explicit SlitForm(Slit * slit, OpticalDeviceTabWidget * parent = 0);
    ~SlitForm();
private slots:
    void geometry();
private:
    bool m_geometry;
    Slit * m_slit;
    QLineEdit * m_nameLineEdit;
    QDoubleSpinBox * m_xSpinBox;
    QDoubleSpinBox * m_ySpinBox;
    QDoubleSpinBox * m_angleSpinBox;
    QDoubleSpinBox * m_radiusSpinBox;
    QDoubleSpinBox * m_slitRadiusSpinBox;
    QPushButton * m_applyButton;
    QPushButton * m_cancelButton;

public: //OpticalDeviceForm
    QString name() override;
private:
    void apply() override;
    void cancel() override;
    void changed() override;
};

#endif // SLITFORM_H
