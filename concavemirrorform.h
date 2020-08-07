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
    Q_OBJECT
public:
    explicit ConcaveMirrorForm(ConcaveMirror *ConcaveMirror, OpticalDeviceTabWidget *parent = 0);
    ~ConcaveMirrorForm();
private slots:
    void geometry();
private:
    bool m_geometry;
    ConcaveMirror * m_concaveMirror;
    QLineEdit * m_nameLineEdit;
    QDoubleSpinBox * m_xSpinBox;
    QDoubleSpinBox * m_ySpinBox;
    QDoubleSpinBox * m_angleSpinBox;
    QDoubleSpinBox * m_radiusSpinBox;
    QDoubleSpinBox * m_focalLengthSpinBox;
    QPushButton * m_applyButton;
    QPushButton * m_cancelButton;

public: //OpticalDeviceForm
    QString name() override;
private:
    void apply() override;
    void cancel() override;
    void changed() override;
};

#endif // CONCAVEMIRRORFORM_H
