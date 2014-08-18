#include "diffractiongratingform.h"

#include "diffractiongrating.h"
#include "opticaldevicetabwidget.h"
#include "precisedoublespinbox.h"
#include "settings.h"

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

DiffractionGratingForm::DiffractionGratingForm(DiffractionGrating * diffractionGrating, OpticalDeviceTabWidget * parent) :
    OpticalDeviceForm(parent),
    m_geometry(false),
    m_reflection(false),
    m_diffractionGrating(diffractionGrating)
{
    m_nameLineEdit = new QLineEdit();

    m_xSpinBox = new PreciseDoubleSpinBox();
    m_xSpinBox->setDecimals(Settings::decimals);
    m_xSpinBox->setRange(Settings::minX, Settings::maxX);
    m_xSpinBox->setSuffix(" mm");

    m_ySpinBox = new PreciseDoubleSpinBox();
    m_ySpinBox->setDecimals(Settings::decimals);
    m_ySpinBox->setRange(Settings::minY, Settings::maxY);
    m_ySpinBox->setSuffix(" mm");

    m_angleSpinBox = new PreciseDoubleSpinBox();
    m_angleSpinBox->setDecimals(Settings::decimals);
    m_angleSpinBox->setRange(Settings::minAngle, Settings::maxAngle);
    m_angleSpinBox->setSuffix("\260");

    m_radiusSpinBox = new PreciseDoubleSpinBox();
    m_radiusSpinBox->setDecimals(Settings::decimals);
    m_radiusSpinBox->setRange(Settings::minRadius, Settings::maxRadius);
    m_radiusSpinBox->setSuffix(" mm");

    m_blazeAngleSpinBox = new PreciseDoubleSpinBox();
    m_blazeAngleSpinBox->setDecimals(Settings::decimals);
    m_blazeAngleSpinBox->setRange(Settings::minBlazingAngle, Settings::maxBlazingAngle);
    m_blazeAngleSpinBox->setSuffix("\260");

    m_densitySpinBox = new PreciseDoubleSpinBox();
    m_densitySpinBox->setDecimals(Settings::decimals);
    m_densitySpinBox->setRange(Settings::minDensity, Settings::maxDensity);
    m_densitySpinBox->setSuffix( QString::fromUtf8(" mm\u207b\u00b9"));

    m_applyButton = new QPushButton("Apply");
    m_applyButton->setAutoDefault(true);

    m_cancelButton = new QPushButton("Cancel");
    m_cancelButton->setAutoDefault(true);

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

    cancel();

    connect(m_nameLineEdit, SIGNAL(textChanged(QString const &)), this, SLOT(changed()));
    connect(m_nameLineEdit, SIGNAL(textChanged(QString const &)), parent, SLOT(changed()));
    connect(m_xSpinBox, SIGNAL(valueChanged(double)), this, SLOT(geometry()));
    connect(m_xSpinBox, SIGNAL(valueChanged(double)), parent, SLOT(changed()));
    connect(m_ySpinBox, SIGNAL(valueChanged(double)), this, SLOT(geometry()));
    connect(m_ySpinBox, SIGNAL(valueChanged(double)), parent, SLOT(changed()));
    connect(m_angleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(geometry()));
    connect(m_angleSpinBox, SIGNAL(valueChanged(double)), parent, SLOT(changed()));
    connect(m_radiusSpinBox, SIGNAL(valueChanged(double)), this, SLOT(geometry()));
    connect(m_radiusSpinBox, SIGNAL(valueChanged(double)), parent, SLOT(changed()));
    connect(m_blazeAngleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(changed()));
    connect(m_blazeAngleSpinBox, SIGNAL(valueChanged(double)), parent, SLOT(changed()));
    connect(m_densitySpinBox, SIGNAL(valueChanged(double)), this, SLOT(reflection()));
    connect(m_densitySpinBox, SIGNAL(valueChanged(double)), parent, SLOT(changed()));
    connect(m_applyButton, SIGNAL(clicked()), this, SLOT(apply()));
    connect(m_applyButton, SIGNAL(clicked()), parent, SLOT(apply()));
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(m_cancelButton, SIGNAL(clicked()), parent, SLOT(cancel()));
}

DiffractionGratingForm::~DiffractionGratingForm()
{
}

void DiffractionGratingForm::geometry()
{
    m_geometry = true;
    changed();
}

void DiffractionGratingForm::reflection()
{
    m_reflection = true;
    changed();
}

QString DiffractionGratingForm::name()
{

    return m_nameLineEdit->text();
}

void DiffractionGratingForm::apply()
{
    m_diffractionGrating->setName(m_nameLineEdit->text());
    if(m_geometry)
    {
        m_diffractionGrating->setX(m_xSpinBox->value());
        m_diffractionGrating->setY(m_ySpinBox->value());
        m_diffractionGrating->setRotation(-m_angleSpinBox->value());
        m_diffractionGrating->setRadius(m_radiusSpinBox->value());
        m_diffractionGrating->setBlazeAngle(m_blazeAngleSpinBox->value());
        m_diffractionGrating->setDensity(m_densitySpinBox->value());
        m_diffractionGrating->build(true);
    }
    else if(m_reflection)
    {
        m_diffractionGrating->setDensity(m_densitySpinBox->value());
        m_diffractionGrating->build(false);
    }
    m_geometry = false;
    m_reflection = false;
    m_applyButton->setEnabled(false);
    m_cancelButton->setEnabled(false);
}

void DiffractionGratingForm::cancel()
{
    m_nameLineEdit->setText(m_diffractionGrating->name());
    m_xSpinBox->setValue(m_diffractionGrating->x());
    m_ySpinBox->setValue(m_diffractionGrating->y());
    m_angleSpinBox->setValue(-m_diffractionGrating->rotation());
    m_radiusSpinBox->setValue(m_diffractionGrating->radius());
    m_densitySpinBox->setValue(m_diffractionGrating->density());
    m_blazeAngleSpinBox->setValue(m_diffractionGrating->blazeAngle());
    m_geometry = false;
    m_reflection = false;
    m_applyButton->setEnabled(false);
    m_cancelButton->setEnabled(false);
}

void DiffractionGratingForm::changed()
{
    m_applyButton->setEnabled(true);
    m_cancelButton->setEnabled(true);
}
