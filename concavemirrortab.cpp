#include "concavemirrortab.h"
#include "concavemirror.h"
#include "settings.h"
#include <QLabel>
#include <QGridLayout>
#include <QDoubleSpinBox>

ConcaveMirrorTab::ConcaveMirrorTab(ConcaveMirror *concaveMirror, MainWindow *mainWindow, QWidget *parent) :
    ReflectorTab(concaveMirror, mainWindow, parent),
    m_concaveMirror(concaveMirror)
{
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

    m_layout->addWidget(m_radiusLabel, 2, 2);
    m_layout->addWidget(m_radiusSpinBox, 2, 3);
    m_layout->addWidget(m_focalLengthLabel, 3, 0);
    m_layout->addWidget(m_focalLengthSpinBox, 3, 1);

    connect(m_radiusSpinBox, SIGNAL(valueChanged(double)), this, SLOT(radiusValueChanged(double)));
    connect(m_focalLengthSpinBox, SIGNAL(valueChanged(double)), this, SLOT(focalLengthValueChanged(double)));
}

void ConcaveMirrorTab::radiusValueChanged(double value)
{
    if(value <= 2 * m_focalLengthSpinBox->value())
    {
        m_radiusSpinBox->setSuffix("");
        m_focalLengthSpinBox->setSuffix("");
        m_concaveMirror->setRadius(value);
        m_concaveMirror->setFocalLength(m_focalLengthSpinBox->value());
    }
    else
    {
        m_radiusSpinBox->setSuffix(" !");
        m_focalLengthSpinBox->setSuffix(" !");
    }
}

void ConcaveMirrorTab::focalLengthValueChanged(double value)
{
    if(m_radiusSpinBox->value() <= 2 * value)
    {
        m_radiusSpinBox->setSuffix("");
        m_focalLengthSpinBox->setSuffix("");
        m_concaveMirror->setRadius(m_radiusSpinBox->value());
        m_concaveMirror->setFocalLength(value);
    }
    else
    {
        m_radiusSpinBox->setSuffix(" !");
        m_focalLengthSpinBox->setSuffix(" !");
    }
}
