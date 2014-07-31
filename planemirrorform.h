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
    Q_OBJECT
public:
    explicit PlaneMirrorForm(PlaneMirror * PlaneMirror, OpticalDeviceTabWidget * parent = 0);
    ~PlaneMirrorForm();
private slots:
    void geometry();
private:
    bool m_geometry;
    PlaneMirror * m_planeMirror;
    QLineEdit * m_nameLineEdit;
    QDoubleSpinBox * m_xSpinBox;
    QDoubleSpinBox * m_ySpinBox;
    QDoubleSpinBox * m_angleSpinBox;
    QDoubleSpinBox * m_radiusSpinBox;
    QPushButton * m_applyButton;
    QPushButton * m_cancelButton;

public: //OpticalDeviceForm
    QString name() override;
private:
    void apply() override;
    void cancel() override;
    void changed() override;
};
#endif // PLANEMIRRORFORM_H
