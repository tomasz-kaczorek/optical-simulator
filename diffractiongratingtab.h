#ifndef DIFFRACTIONGRATINGTAB_H
#define DIFFRACTIONGRATINGTAB_H

#include "reflectortab.h"

class DiffractionGrating;
class QDoubleSpinBox;

class DiffractionGratingTab : public ReflectorTab
{
    Q_OBJECT
public:
    explicit DiffractionGratingTab(DiffractionGrating *diffractionGrating, MainWindow *mainWindow, QWidget *parent = 0);
private:
    DiffractionGrating *m_diffractionGrating;
    QLabel *m_radiusLabel;
    QDoubleSpinBox *m_radiusSpinBox;
    QLabel *m_densityLabel;
    QDoubleSpinBox *m_densitySpinBox;
    QLabel *m_blazingAngleLabel;
    QDoubleSpinBox *m_blazingAngleSpinBox;
public slots:
    void radiusValueChanged(double value);
    void densityValueChanged(double value);
    void blazingAngleValueChanged(double value);
};

#endif // DIFFRACTIONGRATINGTAB_H
