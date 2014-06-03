#ifndef CONCAVEMIRRORTAB_H
#define CONCAVEMIRRORTAB_H

#include "reflectortab.h"

class ConcaveMirror;
class QDoubleSpinBox;

class ConcaveMirrorTab : public ReflectorTab
{
    Q_OBJECT
public:
    explicit ConcaveMirrorTab(ConcaveMirror *concaveMirror, MainWindow *mainWindow, QWidget *parent = 0);
private:
    ConcaveMirror *m_concaveMirror;
    QLabel *m_radiusLabel;
    QDoubleSpinBox *m_radiusSpinBox;
    QLabel *m_focalLengthLabel;
    QDoubleSpinBox *m_focalLengthSpinBox;
public slots:
    void radiusValueChanged(double value);
    void focalLengthValueChanged(double value);
};

#endif // CONCAVEMIRRORTAB_H
