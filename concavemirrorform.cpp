#include "concavemirrorform.h"

#include "concavemirror.h"
#include "settings.h"

#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

ConcaveMirrorForm::ConcaveMirrorForm(ConcaveMirror *concaveMirror, QWidget *parent) :
    OpticalDeviceForm(parent),
    m_concaveMirror(concaveMirror)
{
    m_layout = new QGridLayout(this);

    m_nameLabel = new QLabel(tr("name:"), this);
    m_nameLineEdit = new QLineEdit(QString("Concave Mirror"), this);

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

    m_focalLengthLabel = new QLabel(tr("focal length:"), this);
    m_focalLengthSpinBox = new QDoubleSpinBox(this);
    m_focalLengthSpinBox->setDecimals(Settings::decimals);
    m_focalLengthSpinBox->setSingleStep(Settings::epsilon);
    m_focalLengthSpinBox->setRange(Settings::minFocalLength, Settings::maxFocalLength);

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
    m_layout->addWidget(m_focalLengthLabel, 3, 0);
    m_layout->addWidget(m_focalLengthSpinBox, 3, 1);

    apply();
}

ConcaveMirrorForm::~ConcaveMirrorForm()
{
    delete m_concaveMirror;
}

QString ConcaveMirrorForm::name()
{
    return m_nameLineEdit->text();
}

void ConcaveMirrorForm::apply()
{
    m_concaveMirror->setName(m_nameLineEdit->text());
    m_concaveMirror->setX(m_xSpinBox->value());
    m_concaveMirror->setY(m_ySpinBox->value());
    m_concaveMirror->setRotation(m_angleSpinBox->value());
    m_concaveMirror->setRadius(m_radiusSpinBox->value());
    m_concaveMirror->setFocalLength(m_focalLengthSpinBox->value());
    m_concaveMirror->geometryChanged();
}

void ConcaveMirrorForm::cancel()
{
    m_nameLineEdit->setText(m_concaveMirror->name());
    m_xSpinBox->setValue(m_concaveMirror->x());
    m_ySpinBox->setValue(m_concaveMirror->y());
    m_angleSpinBox->setValue(m_concaveMirror->rotation());
    m_radiusSpinBox->setValue(m_concaveMirror->radius());
    m_focalLengthSpinBox->setValue(m_concaveMirror->focalLength());
}
