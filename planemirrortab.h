#ifndef PLANEMIRRORTAB_H
#define PLANEMIRRORTAB_H

#include "reflectortab.h"

class PlaneMirror;

class PlaneMirrorTab : public ReflectorTab
{
    Q_OBJECT
public:
    explicit PlaneMirrorTab(PlaneMirror *planeMirror, MainWindow *mainWindow, QWidget *parent = 0);
    ~PlaneMirrorTab();
private:
    PlaneMirror *m_planeMirror;
    QLabel *m_radiusLabel;
    QDoubleSpinBox *m_radiusSpinBox;
public slots:
    void radiusValueChanged(double value);
};

#endif // PLANEMIRRORTAB_H
