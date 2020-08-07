#include "planemirrorform.h"

#include "opticaldevicetabwidget.h"
#include "planemirror.h"
#include "precisedoublespinbox.h"
#include "settings.h"

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

PlaneMirrorForm::PlaneMirrorForm(PlaneMirror * planeMirror, OpticalDeviceTabWidget * parent) :
    OpticalDeviceForm(parent),
    m_geometry(false),
    m_planeMirror(planeMirror)
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
    m_angleSpinBox->setSuffix(QString::fromUtf8("\u00B0"));

    m_radiusSpinBox = new PreciseDoubleSpinBox();
    m_radiusSpinBox->setDecimals(Settings::decimals);
    m_radiusSpinBox->setRange(Settings::minRadius, Settings::maxRadius);
    m_radiusSpinBox->setSuffix(" mm");

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
    innerLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding), 3, 0, 1, 4);

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
    connect(m_applyButton, SIGNAL(clicked()), this, SLOT(apply()));
    connect(m_applyButton, SIGNAL(clicked()), parent, SLOT(apply()));
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(m_cancelButton, SIGNAL(clicked()), parent, SLOT(cancel()));
}

PlaneMirrorForm::~PlaneMirrorForm()
{
}

void PlaneMirrorForm::geometry()
{
    m_geometry = true;
    changed();
}

QString PlaneMirrorForm::name()
{
    return m_nameLineEdit->text();
}

void PlaneMirrorForm::apply()
{
    m_planeMirror->setName(m_nameLineEdit->text());
    if(m_geometry)
    {
        m_planeMirror->setX(m_xSpinBox->value());
        m_planeMirror->setY(m_ySpinBox->value());
        m_planeMirror->setRotation(-m_angleSpinBox->value());
        m_planeMirror->setRadius(m_radiusSpinBox->value());
        m_planeMirror->build();
    }
    m_geometry = false;
    m_applyButton->setEnabled(false);
    m_cancelButton->setEnabled(false);
}

void PlaneMirrorForm::cancel()
{
    m_nameLineEdit->setText(m_planeMirror->name());
    m_xSpinBox->setValue(m_planeMirror->x());
    m_ySpinBox->setValue(m_planeMirror->y());
    m_angleSpinBox->setValue(-m_planeMirror->rotation());
    m_radiusSpinBox->setValue(m_planeMirror->radius());
    m_geometry = false;
    m_applyButton->setEnabled(false);
    m_cancelButton->setEnabled(false);
}

void PlaneMirrorForm::changed()
{
    m_applyButton->setEnabled(true);
    m_cancelButton->setEnabled(true);
}
