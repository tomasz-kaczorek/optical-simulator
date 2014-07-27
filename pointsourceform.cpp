#include "pointsourceform.h"

#include "aimdialog.h"
#include "opticaldevicetabwidget.h"
#include "pointsource.h"
#include "settings.h"

#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPlastiqueStyle>
#include <QPushButton>
#include <QSpinBox>

PointSourceForm::PointSourceForm(PointSource * pointSource, OpticalDeviceTabWidget * parent) :
    OpticalDeviceForm(parent),
    m_pointSource(pointSource)
{
    m_nameLineEdit = new QLineEdit();
    m_nameLineEdit->setText(m_pointSource->name());
    connect(m_nameLineEdit, SIGNAL(textChanged(QString const &)), this, SLOT(changed()));
    connect(m_nameLineEdit, SIGNAL(textChanged(QString const &)), parent, SLOT(changed()));

    m_xSpinBox = new QDoubleSpinBox();
    m_xSpinBox->setDecimals(Settings::decimals);
    m_xSpinBox->setSingleStep(Settings::epsilon);
    m_xSpinBox->setRange(Settings::minX, Settings::maxX);
    m_xSpinBox->setValue(m_pointSource->x());
    connect(m_xSpinBox, SIGNAL(valueChanged(double)), this, SLOT(changed()));
    connect(m_xSpinBox, SIGNAL(valueChanged(double)), parent, SLOT(changed()));

    m_ySpinBox = new QDoubleSpinBox();
    m_ySpinBox->setDecimals(Settings::decimals);
    m_ySpinBox->setSingleStep(Settings::epsilon);
    m_ySpinBox->setRange(Settings::minY, Settings::maxY);
    m_ySpinBox->setValue(m_pointSource->y());
    connect(m_ySpinBox, SIGNAL(valueChanged(double)), this, SLOT(changed()));
    connect(m_ySpinBox, SIGNAL(valueChanged(double)), parent, SLOT(changed()));

    m_beginAngleSpinBox = new QDoubleSpinBox();
    m_beginAngleSpinBox->setDecimals(Settings::decimals);
    m_beginAngleSpinBox->setSingleStep(Settings::epsilon);
    m_beginAngleSpinBox->setRange(Settings::minAngle, Settings::maxAngle);
    m_beginAngleSpinBox->setValue(m_pointSource->beginAngle());
    connect(m_beginAngleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(changed()));
    connect(m_beginAngleSpinBox, SIGNAL(valueChanged(double)), parent, SLOT(changed()));

    m_endAngleSpinBox = new QDoubleSpinBox();
    m_endAngleSpinBox->setDecimals(Settings::decimals);
    m_endAngleSpinBox->setSingleStep(Settings::epsilon);
    m_endAngleSpinBox->setRange(Settings::minAngle, Settings::maxAngle);
    m_endAngleSpinBox->setValue(m_pointSource->endAngle());
    connect(m_endAngleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(changed()));
    connect(m_endAngleSpinBox, SIGNAL(valueChanged(double)), parent, SLOT(changed()));

    m_quantitySpinBox = new QSpinBox();
    m_quantitySpinBox->setSingleStep(1);
    m_quantitySpinBox->setRange(Settings::minQuantity, Settings::maxQuantity);
    m_quantitySpinBox->setValue(m_pointSource->quantity());
    connect(m_quantitySpinBox, SIGNAL(valueChanged(int)), this, SLOT(changed()));
    connect(m_quantitySpinBox, SIGNAL(valueChanged(int)), parent, SLOT(changed()));

    m_wavelengthSpinBox = new QDoubleSpinBox();
    m_wavelengthSpinBox->setDecimals(Settings::decimals);
    m_wavelengthSpinBox->setSingleStep(Settings::epsilon);
    m_wavelengthSpinBox->setRange(Settings::minWavelength, Settings::maxWavelength);
    m_wavelengthSpinBox->setValue(m_pointSource->wavelength());
    connect(m_wavelengthSpinBox, SIGNAL(valueChanged(double)), this, SLOT(changed()));
    connect(m_wavelengthSpinBox, SIGNAL(valueChanged(double)), parent, SLOT(changed()));

    QGroupBox * ordersGroupBox = new QGroupBox("visible orders");
    ordersGroupBox->setStyle(new QPlastiqueStyle());

    m_orderCheckBoxes[0] = new QCheckBox("-2");
    m_orderCheckBoxes[0]->setChecked(m_pointSource->order(-2));
    connect(m_orderCheckBoxes[0], SIGNAL(stateChanged(int)), this, SLOT(changed()));
    connect(m_orderCheckBoxes[0], SIGNAL(stateChanged(int)), parent, SLOT(changed()));
    m_orderCheckBoxes[1] = new QCheckBox("-1");
    m_orderCheckBoxes[1]->setChecked(m_pointSource->order(-1));
    connect(m_orderCheckBoxes[1], SIGNAL(stateChanged(int)), this, SLOT(changed()));
    connect(m_orderCheckBoxes[1], SIGNAL(stateChanged(int)), parent, SLOT(changed()));
    m_orderCheckBoxes[2] = new QCheckBox("0");
    m_orderCheckBoxes[2]->setChecked(m_pointSource->order(0));
    connect(m_orderCheckBoxes[2], SIGNAL(stateChanged(int)), this, SLOT(changed()));
    connect(m_orderCheckBoxes[2], SIGNAL(stateChanged(int)), parent, SLOT(changed()));
    m_orderCheckBoxes[3] = new QCheckBox("+1");
    m_orderCheckBoxes[3]->setChecked(m_pointSource->order(1));
    connect(m_orderCheckBoxes[3], SIGNAL(stateChanged(int)), this, SLOT(changed()));
    connect(m_orderCheckBoxes[3], SIGNAL(stateChanged(int)), parent, SLOT(changed()));
    m_orderCheckBoxes[4] = new QCheckBox("+2");
    m_orderCheckBoxes[4]->setChecked(m_pointSource->order(2));
    connect(m_orderCheckBoxes[4], SIGNAL(stateChanged(int)), this, SLOT(changed()));
    connect(m_orderCheckBoxes[4], SIGNAL(stateChanged(int)), parent, SLOT(changed()));

    m_activeCheckBox = new QCheckBox("active");
    m_activeCheckBox->setChecked(m_pointSource->active());
    connect(m_activeCheckBox, SIGNAL(stateChanged(int)), this, SLOT(changed()));
    connect(m_activeCheckBox, SIGNAL(stateChanged(int)), parent, SLOT(changed()));

    m_aimButton = new QPushButton("aim");
    m_aimButton->setAutoDefault(true);
    connect(m_aimButton, SIGNAL(clicked()), this, SLOT(aim()));

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

    QGridLayout * orderLayout = new QGridLayout();

    orderLayout->addWidget(m_orderCheckBoxes[0], 1, 0);
    orderLayout->addWidget(m_orderCheckBoxes[1], 0, 0);
    orderLayout->addWidget(m_orderCheckBoxes[2], 0, 1);
    orderLayout->addWidget(m_orderCheckBoxes[3], 0, 2);
    orderLayout->addWidget(m_orderCheckBoxes[4], 1, 2);

    ordersGroupBox->setLayout(orderLayout);

    QGridLayout * innerLayout = new QGridLayout();

    innerLayout->addWidget(new QLabel("name:"), 0, 0);
    innerLayout->addWidget(m_nameLineEdit, 0, 1, 1, 3);
    innerLayout->addWidget(new QLabel("x:"), 1, 0);
    innerLayout->addWidget(m_xSpinBox, 1, 1);
    innerLayout->addWidget(new QLabel("y:"), 1, 2);
    innerLayout->addWidget(m_ySpinBox, 1, 3);
    innerLayout->addWidget(new QLabel("angle #1:"), 2, 0);
    innerLayout->addWidget(m_beginAngleSpinBox, 2, 1);
    innerLayout->addWidget(new QLabel("angle #2:"), 2, 2);
    innerLayout->addWidget(m_endAngleSpinBox, 2, 3);
    innerLayout->addWidget(new QLabel("quantity:"), 3, 0);
    innerLayout->addWidget(m_quantitySpinBox, 3, 1);
    innerLayout->addWidget(new QLabel("wavelength:"), 3, 2);
    innerLayout->addWidget(m_wavelengthSpinBox, 3, 3);
    innerLayout->addWidget(ordersGroupBox, 0, 4, 3, 3);
    innerLayout->addWidget(m_aimButton, 3, 4, 1, 2);
    innerLayout->addWidget(m_activeCheckBox, 3, 6);

    QGridLayout * outerLayout = new QGridLayout();

    outerLayout->addLayout(innerLayout, 0, 0, 1, 2);
    outerLayout->addWidget(m_applyButton, 1, 0);
    outerLayout->addWidget(m_cancelButton, 1, 1);

    setLayout(outerLayout);
}

PointSourceForm::~PointSourceForm()
{
}

QString PointSourceForm::name()
{
    return m_pointSource->name();
}

void PointSourceForm::aim()
{
        AimDialog aimDialog(m_pointSource, this);
        if(aimDialog.exec() == QDialog::Accepted)
        {
            if(aimDialog.hasBeginPoint())
            {
                QLineF line(m_pointSource->pos(), aimDialog.beginPoint());
                m_beginAngleSpinBox->setValue(90 - line.angle());
            }
            if(aimDialog.hasEndPoint())
            {
                QLineF line(m_pointSource->pos(), aimDialog.endPoint());
                m_endAngleSpinBox->setValue(90 - line.angle());
            }
        }
}

void PointSourceForm::apply()
{
    if(m_pointSource->name() != m_nameLineEdit->text()) m_pointSource->setName(m_nameLineEdit->text());
    bool array[5];
    for(int i = 0; i < 5; ++i) array[i] = m_orderCheckBoxes[i]->isChecked();
    m_pointSource->setGeometry(m_xSpinBox->value(), m_ySpinBox->value(), m_beginAngleSpinBox->value(), m_endAngleSpinBox->value(), m_quantitySpinBox->value(), m_wavelengthSpinBox->value(), array, m_activeCheckBox->isChecked());
    m_applyButton->setEnabled(false);
    m_cancelButton->setEnabled(false);
}

void PointSourceForm::cancel()
{
    m_nameLineEdit->setText(m_pointSource->name());
    m_xSpinBox->setValue(m_pointSource->x());
    m_ySpinBox->setValue(m_pointSource->y());
    m_beginAngleSpinBox->setValue(m_pointSource->beginAngle());
    m_endAngleSpinBox->setValue(m_pointSource->endAngle());
    m_quantitySpinBox->setValue(m_pointSource->quantity());
    m_wavelengthSpinBox->setValue(m_pointSource->wavelength());
    m_orderCheckBoxes[0]->setChecked(m_pointSource->order(-2));
    m_orderCheckBoxes[1]->setChecked(m_pointSource->order(-1));
    m_orderCheckBoxes[2]->setChecked(m_pointSource->order(0));
    m_orderCheckBoxes[3]->setChecked(m_pointSource->order(1));
    m_orderCheckBoxes[4]->setChecked(m_pointSource->order(2));
    m_activeCheckBox->setChecked(m_pointSource->active());
    m_applyButton->setEnabled(false);
    m_cancelButton->setEnabled(false);
}

void PointSourceForm::changed()
{
    m_applyButton->setEnabled(true);
    m_cancelButton->setEnabled(true);
}
