#ifndef CONCAVEMIRRORFORM_H
#define CONCAVEMIRRORFORM_H

#include "opticaldeviceform.h"

class ConcaveMirror;

class QDoubleSpinBox;
class QGridLayout;
class QLabel;
class QLineEdit;

class ConcaveMirrorForm : public OpticalDeviceForm
{
public:
    explicit ConcaveMirrorForm(ConcaveMirror *concaveMirror, QWidget *parent = 0);
    ~ConcaveMirrorForm();
    QString name();
    void apply();
    void cancel();
private:
    ConcaveMirror *m_concaveMirror;
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
    QLabel *m_focalLengthLabel;
    QDoubleSpinBox *m_focalLengthSpinBox;
};

#endif // CONCAVEMIRRORFORM_H
