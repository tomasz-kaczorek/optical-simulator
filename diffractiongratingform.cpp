#include "diffractiongratingform.h"

#include "diffractiongrating.h"
#include "settings.h"

#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

DiffractionGratingForm::DiffractionGratingForm(DiffractionGrating *diffractionGrating, QWidget *parent) :
    OpticalDeviceForm(parent),
    m_diffractionGrating(diffractionGrating)
{
    m_layout = new QGridLayout(this);

    m_nameLabel = new QLabel(tr("name:"), this);
    m_nameLineEdit = new QLineEdit(QString("Diffraction Grating"), this);

    m_xLabel = new QLabel(tr("x:"), this);
    m_xSpinBox = new QDoubleSpinBox(this);
    m_xSpinBox->setDecimals(Settings::decimals);
    m_xSpinBox->setSingleStep(Settings::epsilon);
    m_xSpinBox->setRange(Settings::minX, Settings::maxX);

    m_yLabel = new QLabel(tr("y:"), this);
    m_ySpinBox = new QDoubleSpinBox(this);
    m_ySpinBox->setDecimals(Settings::decimals);
    m_ySpinBox->setSingleStep(Settings::epsilon);
    m_ySpinBox->setRange(Settings::minY, Settings::maxY);

    m_angleLabel = new QLabel(tr("angle:"), this);
    m_angleSpinBox = new QDoubleSpinBox(this);
    m_angleSpinBox->setDecimals(Settings::decimals);
    m_angleSpinBox->setSingleStep(Settings::epsilon);
    m_angleSpinBox->setRange(Settings::minAngle, Settings::maxAngle);

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

    m_layout->addWidget(m_nameLabel, 0, 0);
    m_layout->addWidget(m_nameLineEdit, 0, 1, 1, 3);
    m_layout->addWidget(m_xLabel, 1, 0);
    m_layout->addWidget(m_xSpinBox, 1, 1);
    m_layout->addWidget(m_yLabel, 1, 2);
    m_layout->addWidget(m_ySpinBox, 1, 3);
    m_layout->addWidget(m_angleLabel, 2, 0);
    m_layout->addWidget(m_angleSpinBox, 2, 1);
    m_layout->addWidget(m_radiusLabel, 2, 2);
    m_layout->addWidget(m_radiusSpinBox, 2, 3);
    m_layout->addWidget(m_densityLabel, 3, 0);
    m_layout->addWidget(m_densitySpinBox, 3, 1);
    m_layout->addWidget(m_blazingAngleLabel, 3, 2);
    m_layout->addWidget(m_blazingAngleSpinBox, 3, 3);

    apply();
}

DiffractionGratingForm::~DiffractionGratingForm()
{
    delete m_diffractionGrating;
}

QString DiffractionGratingForm::name()
{

    return m_nameLineEdit->text();
}

void DiffractionGratingForm::apply()
{
    m_diffractionGrating->setName(m_nameLineEdit->text());
    m_diffractionGrating->setX(m_xSpinBox->value());
    m_diffractionGrating->setY(m_ySpinBox->value());
    m_diffractionGrating->setRotation(m_angleSpinBox->value());
    m_diffractionGrating->setRadius(m_radiusSpinBox->value());
    m_diffractionGrating->setDensity(m_densitySpinBox->value());
    m_diffractionGrating->setBlazingAngle(m_blazingAngleSpinBox->value());
    m_diffractionGrating->geometryChanged();
}

void DiffractionGratingForm::cancel()
{
    m_nameLineEdit->setText(m_diffractionGrating->name());
    m_xSpinBox->setValue(m_diffractionGrating->x());
    m_ySpinBox->setValue(m_diffractionGrating->y());
    m_angleSpinBox->setValue(m_diffractionGrating->rotation());
    m_radiusSpinBox->setValue(m_diffractionGrating->radius());
    m_densitySpinBox->setValue(m_diffractionGrating->density());
    m_blazingAngleSpinBox->setValue(m_diffractionGrating->blazingAngle());
}
