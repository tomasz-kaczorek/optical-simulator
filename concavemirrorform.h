#ifndef CONCAVEMIRRORFORM_H
#define CONCAVEMIRRORFORM_H

#include "opticaldeviceform.h"

class ConcaveMirror;
class OpticalDeviceTabWidget;

class QDoubleSpinBox;
class QLineEdit;
class QPushButton;

class ConcaveMirrorForm : public OpticalDeviceForm
{
public:
    explicit ConcaveMirrorForm(ConcaveMirror *ConcaveMirror, OpticalDeviceTabWidget *parent = 0);
    ~ConcaveMirrorForm();

    QString name();
private:
    void apply();
    void cancel();
    void changed();

    ConcaveMirror * m_concaveMirror;
    QLineEdit * m_nameLineEdit;
    QDoubleSpinBox * m_xSpinBox;
    QDoubleSpinBox * m_ySpinBox;
    QDoubleSpinBox * m_angleSpinBox;
    QDoubleSpinBox * m_radiusSpinBox;
    QDoubleSpinBox * m_focalLengthSpinBox;
    QPushButton * m_applyButton;
    QPushButton * m_cancelButton;
};

#endif // CONCAVEMIRRORFORM_H
