#include "concavemirrorform.h"

#include "concavemirror.h"
#include "opticaldevicetabwidget.h"
#include "settings.h"

#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

ConcaveMirrorForm::ConcaveMirrorForm(ConcaveMirror * concaveMirror, OpticalDeviceTabWidget * parent) :
    OpticalDeviceForm(parent),
    m_concaveMirror(concaveMirror)
{
    m_nameLineEdit = new QLineEdit();
    m_nameLineEdit->setText(m_concaveMirror->name());
    connect(m_nameLineEdit, SIGNAL(textChanged(QString const &)), this, SLOT(changed()));
    connect(m_nameLineEdit, SIGNAL(textChanged(QString const &)), parent, SLOT(changed()));

    m_xSpinBox = new QDoubleSpinBox();
    m_xSpinBox->setDecimals(Settings::decimals);
    m_xSpinBox->setSingleStep(Settings::epsilon);
    m_xSpinBox->setRange(Settings::minX, Settings::maxX);
    m_xSpinBox->setValue(m_concaveMirror->x());
    connect(m_xSpinBox, SIGNAL(valueChanged(double)), this, SLOT(changed()));
    connect(m_xSpinBox, SIGNAL(valueChanged(double)), parent, SLOT(changed()));

    m_ySpinBox = new QDoubleSpinBox();
    m_ySpinBox->setDecimals(Settings::decimals);
    m_ySpinBox->setSingleStep(Settings::epsilon);
    m_ySpinBox->setRange(Settings::minY, Settings::maxY);
    m_ySpinBox->setValue(m_concaveMirror->y());
    connect(m_ySpinBox, SIGNAL(valueChanged(double)), this, SLOT(changed()));
    connect(m_ySpinBox, SIGNAL(valueChanged(double)), parent, SLOT(changed()));

    m_angleSpinBox = new QDoubleSpinBox();
    m_angleSpinBox->setDecimals(Settings::decimals);
    m_angleSpinBox->setSingleStep(Settings::epsilon);
    m_angleSpinBox->setRange(Settings::minAngle, Settings::maxAngle);
    m_angleSpinBox->setValue(m_concaveMirror->rotation());
    connect(m_angleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(changed()));
    connect(m_angleSpinBox, SIGNAL(valueChanged(double)), parent, SLOT(changed()));

    m_radiusSpinBox = new QDoubleSpinBox();
    m_radiusSpinBox->setDecimals(Settings::decimals);
    m_radiusSpinBox->setSingleStep(Settings::epsilon);
    m_radiusSpinBox->setRange(Settings::minRadius, Settings::maxRadius);
    m_radiusSpinBox->setValue(m_concaveMirror->radius());
    connect(m_radiusSpinBox, SIGNAL(valueChanged(double)), this, SLOT(changed()));
    connect(m_radiusSpinBox, SIGNAL(valueChanged(double)), parent, SLOT(changed()));

    m_focalLengthSpinBox = new QDoubleSpinBox();
    m_focalLengthSpinBox->setDecimals(Settings::decimals);
    m_focalLengthSpinBox->setSingleStep(Settings::epsilon);
    m_focalLengthSpinBox->setRange(Settings::minFocalLength, Settings::maxFocalLength);
    m_focalLengthSpinBox->setValue(m_concaveMirror->focalLength());
    connect(m_focalLengthSpinBox, SIGNAL(valueChanged(double)), this, SLOT(changed()));
    connect(m_focalLengthSpinBox, SIGNAL(valueChanged(double)), parent, SLOT(changed()));

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
    innerLayout->addWidget(new QLabel("focal length:"), 3, 0);
    innerLayout->addWidget(m_focalLengthSpinBox, 3, 1);

    QGridLayout * outerLayout = new QGridLayout();

    outerLayout->addLayout(innerLayout, 0, 0, 1, 2);
    outerLayout->addWidget(m_applyButton, 1, 0);
    outerLayout->addWidget(m_cancelButton, 1, 1);

    setLayout(outerLayout);

    apply();
}

ConcaveMirrorForm::~ConcaveMirrorForm()
{
}

QString ConcaveMirrorForm::name()
{
    return m_nameLineEdit->text();
}

void ConcaveMirrorForm::apply()
{
    if(m_concaveMirror->name() != m_nameLineEdit->text()) m_concaveMirror->setName(m_nameLineEdit->text());
    m_concaveMirror->setGeometry(m_xSpinBox->value(), m_ySpinBox->value(), m_angleSpinBox->value(), m_radiusSpinBox->value(), m_focalLengthSpinBox->value());
    m_applyButton->setEnabled(false);
    m_cancelButton->setEnabled(false);
}

void ConcaveMirrorForm::cancel()
{
    m_nameLineEdit->setText(m_concaveMirror->name());
    m_xSpinBox->setValue(m_concaveMirror->x());
    m_ySpinBox->setValue(m_concaveMirror->y());
    m_angleSpinBox->setValue(m_concaveMirror->rotation());
    m_radiusSpinBox->setValue(m_concaveMirror->radius());
    m_focalLengthSpinBox->setValue(m_concaveMirror->focalLength());
    m_applyButton->setEnabled(false);
    m_cancelButton->setEnabled(false);
}

void ConcaveMirrorForm::changed()
{
    m_applyButton->setEnabled(true);
    m_cancelButton->setEnabled(true);
}
