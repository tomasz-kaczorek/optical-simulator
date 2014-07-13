#include "diffractiongratingform.h"

#include "diffractiongrating.h"
#include "opticaldevicetabwidget.h"
#include "settings.h"

#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

DiffractionGratingForm::DiffractionGratingForm(DiffractionGrating * diffractionGrating, OpticalDeviceTabWidget * parent) :
    OpticalDeviceForm(parent),
    m_diffractionGrating(diffractionGrating)
{
    m_nameLineEdit = new QLineEdit();
    m_nameLineEdit->setText(m_diffractionGrating->name());
    connect(m_nameLineEdit, SIGNAL(textChanged(QString const &)), this, SLOT(changed()));
    connect(m_nameLineEdit, SIGNAL(textChanged(QString const &)), parent, SLOT(changed()));

    m_xSpinBox = new QDoubleSpinBox();
    m_xSpinBox->setDecimals(Settings::decimals);
    m_xSpinBox->setSingleStep(Settings::epsilon);
    m_xSpinBox->setRange(Settings::minX, Settings::maxX);
    m_xSpinBox->setValue(m_diffractionGrating->x());
    connect(m_xSpinBox, SIGNAL(valueChanged(double)), this, SLOT(changed()));
    connect(m_xSpinBox, SIGNAL(valueChanged(double)), parent, SLOT(changed()));

    m_ySpinBox = new QDoubleSpinBox();
    m_ySpinBox->setDecimals(Settings::decimals);
    m_ySpinBox->setSingleStep(Settings::epsilon);
    m_ySpinBox->setRange(Settings::minY, Settings::maxY);
    m_ySpinBox->setValue(m_diffractionGrating->y());
    connect(m_ySpinBox, SIGNAL(valueChanged(double)), this, SLOT(changed()));
    connect(m_ySpinBox, SIGNAL(valueChanged(double)), parent, SLOT(changed()));

    m_angleSpinBox = new QDoubleSpinBox();
    m_angleSpinBox->setDecimals(Settings::decimals);
    m_angleSpinBox->setSingleStep(Settings::epsilon);
    m_angleSpinBox->setRange(Settings::minAngle, Settings::maxAngle);
    m_angleSpinBox->setValue(m_diffractionGrating->rotation());
    connect(m_angleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(changed()));
    connect(m_angleSpinBox, SIGNAL(valueChanged(double)), parent, SLOT(changed()));

    m_radiusSpinBox = new QDoubleSpinBox();
    m_radiusSpinBox->setDecimals(Settings::decimals);
    m_radiusSpinBox->setSingleStep(Settings::epsilon);
    m_radiusSpinBox->setRange(Settings::minRadius, Settings::maxRadius);
    m_radiusSpinBox->setValue(m_diffractionGrating->radius());
    connect(m_radiusSpinBox, SIGNAL(valueChanged(double)), this, SLOT(changed()));
    connect(m_radiusSpinBox, SIGNAL(valueChanged(double)), parent, SLOT(changed()));

    m_blazeAngleSpinBox = new QDoubleSpinBox();
    m_blazeAngleSpinBox->setDecimals(Settings::decimals);
    m_blazeAngleSpinBox->setSingleStep(Settings::epsilon);
    m_blazeAngleSpinBox->setRange(Settings::minBlazingAngle, Settings::maxBlazingAngle);
    m_blazeAngleSpinBox->setValue(m_diffractionGrating->blazeAngle());
    connect(m_blazeAngleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(changed()));
    connect(m_blazeAngleSpinBox, SIGNAL(valueChanged(double)), parent, SLOT(changed()));

    m_densitySpinBox = new QDoubleSpinBox();
    m_densitySpinBox->setDecimals(Settings::decimals);
    m_densitySpinBox->setSingleStep(Settings::epsilon);
    m_densitySpinBox->setRange(Settings::minDensity, Settings::maxDensity);
    m_densitySpinBox->setValue(m_diffractionGrating->density());
    connect(m_densitySpinBox, SIGNAL(valueChanged(double)), this, SLOT(changed()));
    connect(m_densitySpinBox, SIGNAL(valueChanged(double)), parent, SLOT(changed()));

    m_applyButton = new QPushButton("Apply");
    m_applyButton->setAutoDefault(true);
    m_applyButton->setEnabled(false);
    connect(m_applyButton, SIGNAL(clicked()), this, SLOT(apply()));
    connect(m_applyButton, SIGNAL(clicked()), parent, SLOT(apply()));

    m_cancelButton = new QPushButton("Cancel");
    m_cancelButton->setAutoDefault(true);
    m_cancelButton->setEnabled(false);
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(m_cancelButton, SIGNAL(clicked()), parent, SLOT(cancel()));

    QGridLayout * innerLayout = new QGridLayout();

    innerLayout->addWidget(new QLabel("name:"), 0, 0);
    innerLayout->addWidget(m_nameLineEdit, 0, 1, 1, 3);
    innerLayout->addWidget(new QLabel("x:"), 1, 0);
    innerLayout->addWidget(m_xSpinBox, 1, 1);
    innerLayout->addWidget(new QLabel("y:"), 1, 2);
    innerLayout->addWidget(m_ySpinBox, 1, 3);
    innerLayout->addWidget(new QLabel("angle:"), 2, 0);
    innerLayout->addWidget(m_angleSpinBox, 2, 1);
    innerLayout->addWidget(new QLabel("radius:"), 2, 2);
    innerLayout->addWidget(m_radiusSpinBox, 2, 3);
    innerLayout->addWidget(new QLabel("blazing angle:"), 3, 0);
    innerLayout->addWidget(m_blazeAngleSpinBox, 3, 1);
    innerLayout->addWidget(new QLabel("density:"), 3, 2);
    innerLayout->addWidget(m_densitySpinBox, 3, 3);

    QGridLayout * outerLayout = new QGridLayout();

    outerLayout->addLayout(innerLayout, 0, 0, 1, 2);
    outerLayout->addWidget(m_applyButton, 1, 0);
    outerLayout->addWidget(m_cancelButton, 1, 1);

    setLayout(outerLayout);
}

DiffractionGratingForm::~DiffractionGratingForm()
{
}

QString DiffractionGratingForm::name()
{

    return m_nameLineEdit->text();
}

void DiffractionGratingForm::apply()
{
    if(m_diffractionGrating->name() != m_nameLineEdit->text()) m_diffractionGrating->setName(m_nameLineEdit->text());
    m_diffractionGrating->setGeometry(m_xSpinBox->value(), m_ySpinBox->value(), m_angleSpinBox->value(), m_radiusSpinBox->value(), m_blazeAngleSpinBox->value(), m_densitySpinBox->value());
    m_applyButton->setEnabled(false);
    m_cancelButton->setEnabled(false);
}

void DiffractionGratingForm::cancel()
{
    m_nameLineEdit->setText(m_diffractionGrating->name());
    m_xSpinBox->setValue(m_diffractionGrating->x());
    m_ySpinBox->setValue(m_diffractionGrating->y());
    m_angleSpinBox->setValue(m_diffractionGrating->rotation());
    m_radiusSpinBox->setValue(m_diffractionGrating->radius());
    m_densitySpinBox->setValue(m_diffractionGrating->density());
    m_blazeAngleSpinBox->setValue(m_diffractionGrating->blazeAngle());
    m_applyButton->setEnabled(false);
    m_cancelButton->setEnabled(false);
}

void DiffractionGratingForm::changed()
{
    m_applyButton->setEnabled(true);
    m_cancelButton->setEnabled(true);
}
