#include "planemirrorform.h"

#include "planemirror.h"
#include "settings.h"

#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

PlaneMirrorForm::PlaneMirrorForm(PlaneMirror *planeMirror, QWidget *parent) :
    OpticalDeviceForm(parent),
    m_planeMirror(planeMirror)
{
    m_layout = new QGridLayout(this);

    m_nameLabel = new QLabel(tr("name:"), this);
    m_nameLineEdit = new QLineEdit(QString("Plane Mirror"), this);

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
    m_layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding), 3, 0, 1, 4);

    apply();
}

PlaneMirrorForm::~PlaneMirrorForm()
{
    delete m_planeMirror;
}

QString PlaneMirrorForm::name()
{
    return m_nameLineEdit->text();
}

void PlaneMirrorForm::apply()
{
    m_planeMirror->setName(m_nameLineEdit->text());
    m_planeMirror->setX(m_xSpinBox->value());
    m_planeMirror->setY(m_ySpinBox->value());
    m_planeMirror->setRotation(m_angleSpinBox->value());
    m_planeMirror->setRadius(m_radiusSpinBox->value());
    m_planeMirror->geometryChanged();
}

void PlaneMirrorForm::cancel()
{
    m_nameLineEdit->setText(m_planeMirror->name());
    m_xSpinBox->setValue(m_planeMirror->x());
    m_ySpinBox->setValue(m_planeMirror->y());
    m_angleSpinBox->setValue(m_planeMirror->rotation());
    m_radiusSpinBox->setValue(m_planeMirror->radius());
}
