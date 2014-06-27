#ifndef PLANEMIRRORFORM_H
#define PLANEMIRRORFORM_H

#include "opticaldeviceform.h"

class PlaneMirror;

class QDoubleSpinBox;
class QGridLayout;
class QLabel;
class QLineEdit;

class PlaneMirrorForm : public OpticalDeviceForm
{
public:
    explicit PlaneMirrorForm(PlaneMirror *planeMirror, QWidget *parent = 0);
    ~PlaneMirrorForm();
    QString name();
    void apply();
    void cancel();
private:
    PlaneMirror *m_planeMirror;
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
};

#endif // PLANEMIRRORFORM_H
