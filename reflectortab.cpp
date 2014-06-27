#include "reflectortab.h"

#include "reflector.h"
#include "settings.h"

#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

ReflectorTab::ReflectorTab(QWidget *parent) :
    QWidget(parent)
{
    m_layout = new QGridLayout(this);

    m_nameLabel = new QLabel(tr("name:"), this);
    m_nameLineEdit = new QLineEdit(this);

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

    m_layout->addWidget(m_nameLabel, 0, 0);
    m_layout->addWidget(m_nameLineEdit, 0, 1, 1, 3);
    m_layout->addWidget(m_xLabel, 1, 0);
    m_layout->addWidget(m_xSpinBox, 1, 1);
    m_layout->addWidget(m_yLabel, 1, 2);
    m_layout->addWidget(m_ySpinBox, 1, 3);
    m_layout->addWidget(m_angleLabel, 2, 0);
    m_layout->addWidget(m_angleSpinBox, 2, 1);

    setLayout(m_layout);
}

ReflectorTab::~ReflectorTab()
{
}

