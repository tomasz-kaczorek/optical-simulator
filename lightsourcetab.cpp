#include "lightsourcetab.h"
#include "lightsource.h"
#include "mainwindow.h"
#include "aimdialog.h"
#include "reflector.h"
#include "settings.h"

#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QCheckBox>
#include <QPushButton>
#include <QGridLayout>
#include <QPlastiqueStyle>
#include <QSpinBox>
#include <QDoubleSpinBox>

LightSourceTab::LightSourceTab(LightSource *lightSource, MainWindow *mainWindow, QWidget *parent) :
    QWidget(parent),
    m_mainWindow(mainWindow),
    m_lightSource(lightSource)
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

    m_beginAngleLabel = new QLabel(tr("angle #1:"), this);
    m_beginAngleSpinBox = new QDoubleSpinBox(this);
    m_beginAngleSpinBox->setDecimals(Settings::decimals);
    m_beginAngleSpinBox->setSingleStep(Settings::epsilon);
    m_beginAngleSpinBox->setRange(Settings::minAngle, Settings::maxAngle);

    m_endAngleLabel = new QLabel(tr("angle #2:"), this);
    m_endAngleSpinBox = new QDoubleSpinBox(this);
    m_endAngleSpinBox->setDecimals(Settings::decimals);
    m_endAngleSpinBox->setSingleStep(Settings::epsilon);
    m_endAngleSpinBox->setRange(Settings::minAngle, Settings::maxAngle);

    m_quantityLabel = new QLabel(tr("count:"), this);
    m_quantitySpinBox = new QSpinBox(this);
    m_quantitySpinBox->setSingleStep(1);
    m_quantitySpinBox->setRange(Settings::minQuantity, Settings::maxQuantity);

    m_wavelengthLabel = new QLabel(tr("wavelength:"), this);
    m_wavelengthSpinBox = new QDoubleSpinBox(this);
    m_wavelengthSpinBox->setDecimals(Settings::decimals);
    m_wavelengthSpinBox->setSingleStep(Settings::epsilon);
    m_wavelengthSpinBox->setRange(Settings::minWavelength, Settings::maxWavelength);

    m_visibleOrdersGroupBox = new QGroupBox(tr("visible orders"), this);
    m_visibleOrdersGroupBox->setStyle(new QPlastiqueStyle()); //ensures frame
    m_visibleOrdersLayout = new QGridLayout(m_visibleOrdersGroupBox);

    m_secondNegativeOrderCheckBox = new QCheckBox(tr("-2"), m_visibleOrdersGroupBox);
    m_firstNegativeOrderCheckBox = new QCheckBox(tr("-1"), m_visibleOrdersGroupBox);
    m_zeroOrderCheckBox = new QCheckBox(tr("0"), m_visibleOrdersGroupBox);
    m_zeroOrderCheckBox->setCheckState(Qt::Checked);
    m_firstPositiveOrderCheckBox = new QCheckBox(tr("+1"), m_visibleOrdersGroupBox);
    m_secondPositiveOrderCheckBox = new QCheckBox(tr("+2"), m_visibleOrdersGroupBox);

    m_aimPushButton = new QPushButton(tr("aim"), this);

    m_activeCheckBox = new QCheckBox(tr("active"), this);
    m_activeCheckBox->setCheckState(Qt::Checked);

    m_layout->addWidget(m_nameLabel, 0, 0);
    m_layout->addWidget(m_nameLineEdit, 0, 1, 1, 3);
    m_layout->addWidget(m_xLabel, 1, 0);
    m_layout->addWidget(m_xSpinBox, 1, 1);
    m_layout->addWidget(m_yLabel, 1, 2);
    m_layout->addWidget(m_ySpinBox, 1, 3);
    m_layout->addWidget(m_beginAngleLabel, 2, 0);
    m_layout->addWidget(m_beginAngleSpinBox, 2, 1);
    m_layout->addWidget(m_endAngleLabel, 2, 2);
    m_layout->addWidget(m_endAngleSpinBox, 2, 3);
    m_layout->addWidget(m_quantityLabel, 3, 0);
    m_layout->addWidget(m_quantitySpinBox, 3, 1);
    m_layout->addWidget(m_wavelengthLabel, 3, 2);
    m_layout->addWidget(m_wavelengthSpinBox, 3, 3);
    m_visibleOrdersLayout->addWidget(m_secondNegativeOrderCheckBox, 1, 0);
    m_visibleOrdersLayout->addWidget(m_firstNegativeOrderCheckBox, 0, 0);
    m_visibleOrdersLayout->addWidget(m_zeroOrderCheckBox, 0, 1);
    m_visibleOrdersLayout->addWidget(m_firstPositiveOrderCheckBox, 0, 2);
    m_visibleOrdersLayout->addWidget(m_secondPositiveOrderCheckBox, 1, 2);
    m_layout->addWidget(m_visibleOrdersGroupBox, 0, 4, 3, 3);
    m_layout->addWidget(m_aimPushButton, 3, 4, 1, 2);
    m_layout->addWidget(m_activeCheckBox, 3, 6);

    connect(m_nameLineEdit, SIGNAL(editingFinished()), this, SLOT(nameEditingFinished()));
    connect(m_xSpinBox, SIGNAL(valueChanged(double)), this, SLOT(xValueChanged(double)));
    connect(m_ySpinBox, SIGNAL(valueChanged(double)), this, SLOT(yValueChanged(double)));
    connect(m_beginAngleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(beginAngleValueChanged(double)));
    connect(m_endAngleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(endAngleValueChanged(double)));
    connect(m_quantitySpinBox, SIGNAL(valueChanged(int)), this, SLOT(quantityValueChanged(int)));
    connect(m_wavelengthSpinBox, SIGNAL(valueChanged(double)), this, SLOT(wavelengthValueChanged(double)));
    connect(m_secondNegativeOrderCheckBox, SIGNAL(stateChanged(int)), this, SLOT(visibleOrdersStateChanged()));
    connect(m_firstNegativeOrderCheckBox, SIGNAL(stateChanged(int)), this, SLOT(visibleOrdersStateChanged()));
    connect(m_zeroOrderCheckBox, SIGNAL(stateChanged(int)), this, SLOT(visibleOrdersStateChanged()));
    connect(m_firstPositiveOrderCheckBox, SIGNAL(stateChanged(int)), this, SLOT(visibleOrdersStateChanged()));
    connect(m_secondPositiveOrderCheckBox, SIGNAL(stateChanged(int)), this, SLOT(visibleOrdersStateChanged()));
    connect(m_activeCheckBox, SIGNAL(stateChanged(int)), this, SLOT(activateStateChanged()));
    connect(m_aimPushButton, SIGNAL(clicked()), this, SLOT(aim()));
}

void LightSourceTab::nameEditingFinished()
{
    if(!m_nameLineEdit->text().isEmpty())
        emit newLabel(this, m_nameLineEdit->text());
}

void LightSourceTab::xValueChanged(double value)
{
    m_lightSource->setX(value);
}

void LightSourceTab::yValueChanged(double value)
{
    m_lightSource->setY(value);
}

void LightSourceTab::beginAngleValueChanged(double value)
{
    m_lightSource->setBeginAngle(value);
}

void LightSourceTab::endAngleValueChanged(double value)
{
    m_lightSource->setEndAngle(value);
}

void LightSourceTab::quantityValueChanged(int value)
{
    m_lightSource->setQuantity(value);
}

void LightSourceTab::wavelengthValueChanged(double value)
{
    m_lightSource->setWavelength(value);
}

void LightSourceTab::visibleOrdersStateChanged()
{
    m_lightSource->setVisibleOrders(-2, m_secondNegativeOrderCheckBox->isChecked());
    m_lightSource->setVisibleOrders(-1, m_firstNegativeOrderCheckBox->isChecked());
    m_lightSource->setVisibleOrders(0, m_zeroOrderCheckBox->isChecked());
    m_lightSource->setVisibleOrders(1, m_firstPositiveOrderCheckBox->isChecked());
    m_lightSource->setVisibleOrders(2, m_secondPositiveOrderCheckBox->isChecked());
}

void LightSourceTab::activateStateChanged()
{
    m_lightSource->setActive(m_activeCheckBox->isChecked());
}

void LightSourceTab::aim()
{
    AimDialog aimDialog(m_mainWindow->getNames());
    if(aimDialog.exec())
    {
        Reflector *reflector = m_mainWindow->getReflector(aimDialog.getIndex());
        if(aimDialog.getChoice() == 0)
        {
            QPointF center = reflector->pos();
            QLineF direction(m_lightSource->x(), m_lightSource->y(), center.x(), center.y());
            m_beginAngleSpinBox->setValue(360-direction.angle());
            m_endAngleSpinBox->setValue(360-direction.angle());
        }
        else if(aimDialog.getChoice() == 1)
        {
            QPointF left = reflector->leftEdge();
            QLineF direction(m_lightSource->x(), m_lightSource->y(), left.x(), left.y());
            m_beginAngleSpinBox->setValue(360-direction.angle());
            m_endAngleSpinBox->setValue(360-direction.angle());
        }
        else if(aimDialog.getChoice() == 2)
        {
            QPointF right = reflector->rightEdge();
            QLineF direction(m_lightSource->x(), m_lightSource->y(), right.x(), right.y());
            m_beginAngleSpinBox->setValue(360-direction.angle());
            m_endAngleSpinBox->setValue(360-direction.angle());
        }
        else if(aimDialog.getChoice() == 3)
        {
            QPointF left = reflector->leftEdge();
            QPointF right = reflector->rightEdge();
            QLineF directionLeft(m_lightSource->x(), m_lightSource->y(), left.x(), left.y());
            QLineF directionRight(m_lightSource->x(), m_lightSource->y(), right.x(), right.y());
            if(directionLeft.angle() < directionRight.angle())
            {
                m_beginAngleSpinBox->setValue(360-directionLeft.angle());
                m_endAngleSpinBox->setValue(360-directionRight.angle());
            }
            else
            {
                m_beginAngleSpinBox->setValue(360-directionRight.angle());
                m_endAngleSpinBox->setValue(360-directionLeft.angle());
            }
        }
    }
}


