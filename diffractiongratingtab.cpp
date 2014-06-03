#include "diffractiongratingtab.h"
#include "diffractiongrating.h"
#include "settings.h"
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QDoubleSpinBox>

DiffractionGratingTab::DiffractionGratingTab(DiffractionGrating *diffractionGrating, MainWindow *mainWindow, QWidget *parent) :
    ReflectorTab(diffractionGrating, mainWindow, parent),
    m_diffractionGrating(diffractionGrating)
{
    m_radiusLabel = new QLabel(tr("radius:"), this);
    m_radiusSpinBox = new QDoubleSpinBox(this);
    m_radiusSpinBox->setDecimals(Settings::decimals);
    m_radiusSpinBox->setSingleStep(Settings::epsilon);
    m_radiusSpinBox->setRange(Settings::minRadius, Settings::maxRadius);

    m_densityLabel = new QLabel(tr("density:"), this);
    m_densitySpinBox = new QDoubleSpinBox(this);
    m_densitySpinBox->setDecimals(Settings::decimals);
    m_densitySpinBox->setSingleStep(Settings::epsilon);
    m_densitySpinBox->setRange(Settings::minDensity, Settings::maxDensity);

    m_blazingAngleLabel = new QLabel(tr("blazing angle:"), this);
    m_blazingAngleSpinBox = new QDoubleSpinBox(this);
    m_blazingAngleSpinBox->setDecimals(Settings::decimals);
    m_blazingAngleSpinBox->setSingleStep(Settings::epsilon);
    m_blazingAngleSpinBox->setRange(Settings::minBlazingAngle, Settings::maxBlazingAngle);

    m_layout->addWidget(m_radiusLabel, 2, 2);
    m_layout->addWidget(m_radiusSpinBox, 2, 3);
    m_layout->addWidget(m_densityLabel, 3, 0);
    m_layout->addWidget(m_densitySpinBox, 3, 1);
    m_layout->addWidget(m_blazingAngleLabel, 3, 2);
    m_layout->addWidget(m_blazingAngleSpinBox, 3, 3);

    connect(m_radiusSpinBox, SIGNAL(valueChanged(double)), this, SLOT(radiusValueChanged(double)));
    connect(m_densitySpinBox, SIGNAL(valueChanged(double)), this, SLOT(densityValueChanged(double)));
    connect(m_blazingAngleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(blazingAngleValueChanged(double)));
}

void DiffractionGratingTab::radiusValueChanged(double value)
{
    m_diffractionGrating->setRadius(value);
}

void DiffractionGratingTab::densityValueChanged(double value)
{
    m_diffractionGrating->setDensity(value);
}

void DiffractionGratingTab::blazingAngleValueChanged(double value)
{
    m_diffractionGrating->setBlazingAngle(value);
}
