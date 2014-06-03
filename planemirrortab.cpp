#include "planemirrortab.h"
#include "planemirror.h"
#include "settings.h"
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QSpacerItem>

PlaneMirrorTab::PlaneMirrorTab(PlaneMirror *planeMirror, MainWindow *mainWindow, QWidget *parent) :
    ReflectorTab(planeMirror, mainWindow, parent),
    m_planeMirror(planeMirror)
{
    m_radiusLabel = new QLabel(tr("radius:"), this);
    m_radiusSpinBox = new QDoubleSpinBox(this);
    m_radiusSpinBox->setDecimals(Settings::decimals);
    m_radiusSpinBox->setSingleStep(Settings::epsilon);
    m_radiusSpinBox->setRange(Settings::minRadius, Settings::maxRadius);

    m_layout->addWidget(m_radiusLabel, 2, 2);
    m_layout->addWidget(m_radiusSpinBox, 2, 3);
    m_layout->addItem(new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding), 3, 0);

    connect(m_radiusSpinBox, SIGNAL(valueChanged(double)), this, SLOT(radiusValueChanged(double)));
}

PlaneMirrorTab::~PlaneMirrorTab()
{
}

void PlaneMirrorTab::radiusValueChanged(double value)
{
    m_planeMirror->setRadius(value);
}
