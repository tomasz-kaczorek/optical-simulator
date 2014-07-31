#include "pointsourceform.h"

#include "aimdialog.h"
#include "opticaldevicetabwidget.h"
#include "pointsource.h"
#include "precisedoublespinbox.h"
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
    m_geometry(false),
    m_reflection(false),
    m_pointSource(pointSource)
{
    m_nameLineEdit = new QLineEdit();

    m_xSpinBox = new QDoubleSpinBox();
    m_xSpinBox->setDecimals(Settings::decimals);
    m_xSpinBox->setRange(Settings::minX, Settings::maxX);

    m_ySpinBox = new QDoubleSpinBox();
    m_ySpinBox->setDecimals(Settings::decimals);
    m_ySpinBox->setRange(Settings::minY, Settings::maxY);

    m_beginAngleSpinBox = new PreciseDoubleSpinBox();
    m_beginAngleSpinBox->setDecimals(Settings::decimals);
    m_beginAngleSpinBox->setRange(Settings::minAngle, Settings::maxAngle);

    m_endAngleSpinBox = new PreciseDoubleSpinBox();
    m_endAngleSpinBox->setDecimals(Settings::decimals);
    m_endAngleSpinBox->setRange(Settings::minAngle, Settings::maxAngle);

    m_quantitySpinBox = new QSpinBox();
    m_quantitySpinBox->setRange(Settings::minQuantity, Settings::maxQuantity);

    m_wavelengthSpinBox = new QDoubleSpinBox();
    m_wavelengthSpinBox->setDecimals(Settings::decimals);
    m_wavelengthSpinBox->setRange(Settings::minWavelength, Settings::maxWavelength);

    QGroupBox * ordersGroupBox = new QGroupBox("visible orders");
    ordersGroupBox->setStyle(new QPlastiqueStyle());

    m_orderCheckBoxes[0] = new QCheckBox("-2");
    m_orderCheckBoxes[1] = new QCheckBox("-1");
    m_orderCheckBoxes[2] = new QCheckBox("0");
    m_orderCheckBoxes[3] = new QCheckBox("+1");
    m_orderCheckBoxes[4] = new QCheckBox("+2");

    m_activeCheckBox = new QCheckBox("active");

    m_aimButton = new QPushButton("aim");
    m_aimButton->setAutoDefault(true);

    m_applyButton = new QPushButton("Apply");
    m_applyButton->setAutoDefault(true);

    m_cancelButton = new QPushButton("Cancel");
    m_cancelButton->setAutoDefault(true);

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
    innerLayout->addWidget(new QLabel("begin angle:"), 2, 0);
    innerLayout->addWidget(m_beginAngleSpinBox, 2, 1);
    innerLayout->addWidget(new QLabel("end angle:"), 2, 2);
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

    cancel();

    connect(m_nameLineEdit, SIGNAL(textChanged(QString const &)), this, SLOT(changed()));
    connect(m_nameLineEdit, SIGNAL(textChanged(QString const &)), parent, SLOT(changed()));
    connect(m_xSpinBox, SIGNAL(valueChanged(double)), this, SLOT(geometry()));
    connect(m_xSpinBox, SIGNAL(valueChanged(double)), parent, SLOT(changed()));
    connect(m_ySpinBox, SIGNAL(valueChanged(double)), this, SLOT(geometry()));
    connect(m_ySpinBox, SIGNAL(valueChanged(double)), parent, SLOT(changed()));
    connect(m_beginAngleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(geometry()));
    connect(m_beginAngleSpinBox, SIGNAL(valueChanged(double)), parent, SLOT(changed()));
    connect(m_endAngleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(geometry()));
    connect(m_endAngleSpinBox, SIGNAL(valueChanged(double)), parent, SLOT(changed()));
    connect(m_quantitySpinBox, SIGNAL(valueChanged(int)), this, SLOT(geometry()));
    connect(m_quantitySpinBox, SIGNAL(valueChanged(int)), parent, SLOT(changed()));
    connect(m_wavelengthSpinBox, SIGNAL(valueChanged(double)), this, SLOT(reflection()));
    connect(m_wavelengthSpinBox, SIGNAL(valueChanged(double)), parent, SLOT(changed()));
    connect(m_orderCheckBoxes[0], SIGNAL(stateChanged(int)), this, SLOT(reflection()));
    connect(m_orderCheckBoxes[0], SIGNAL(stateChanged(int)), parent, SLOT(changed()));
    connect(m_orderCheckBoxes[1], SIGNAL(stateChanged(int)), this, SLOT(reflection()));
    connect(m_orderCheckBoxes[1], SIGNAL(stateChanged(int)), parent, SLOT(changed()));
    connect(m_orderCheckBoxes[2], SIGNAL(stateChanged(int)), this, SLOT(reflection()));
    connect(m_orderCheckBoxes[2], SIGNAL(stateChanged(int)), parent, SLOT(changed()));
    connect(m_orderCheckBoxes[3], SIGNAL(stateChanged(int)), this, SLOT(reflection()));
    connect(m_orderCheckBoxes[3], SIGNAL(stateChanged(int)), parent, SLOT(changed()));
    connect(m_orderCheckBoxes[4], SIGNAL(stateChanged(int)), this, SLOT(reflection()));
    connect(m_orderCheckBoxes[4], SIGNAL(stateChanged(int)), parent, SLOT(changed()));
    connect(m_activeCheckBox, SIGNAL(stateChanged(int)), this, SLOT(geometry()));
    connect(m_activeCheckBox, SIGNAL(stateChanged(int)), parent, SLOT(changed()));
    connect(m_aimButton, SIGNAL(clicked()), this, SLOT(aim()));
    connect(m_applyButton, SIGNAL(clicked()), this, SLOT(apply()));
    connect(m_applyButton, SIGNAL(clicked()), parent, SLOT(apply()));
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(m_cancelButton, SIGNAL(clicked()), parent, SLOT(cancel()));
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
                QLineF line(QPointF(m_xSpinBox->value(), m_ySpinBox->value()), aimDialog.beginPoint());
                m_beginAngleSpinBox->setValue(line.angle());
            }
            if(aimDialog.hasEndPoint())
            {
                QLineF line(QPointF(m_xSpinBox->value(), m_ySpinBox->value()), aimDialog.endPoint());
                m_endAngleSpinBox->setValue(line.angle());
            }
        }
}

void PointSourceForm::geometry()
{
    m_geometry = true;
    changed();
}

void PointSourceForm::reflection()
{
    m_reflection = true;
    changed();
}

void PointSourceForm::apply()
{
    m_pointSource->setName(m_nameLineEdit->text());
    if(m_geometry)
    {
        m_pointSource->setX(m_xSpinBox->value());
        m_pointSource->setY(m_ySpinBox->value());
        m_pointSource->setBeginAngle(m_beginAngleSpinBox->value());
        m_pointSource->setEndAngle(m_endAngleSpinBox->value());
        m_pointSource->setQuantity(m_quantitySpinBox->value());
        m_pointSource->setWavelength(m_wavelengthSpinBox->value());
        m_pointSource->setOrder(0, m_orderCheckBoxes[0]->isChecked());
        m_pointSource->setOrder(1, m_orderCheckBoxes[1]->isChecked());
        m_pointSource->setOrder(2, m_orderCheckBoxes[2]->isChecked());
        m_pointSource->setOrder(3, m_orderCheckBoxes[3]->isChecked());
        m_pointSource->setOrder(4, m_orderCheckBoxes[4]->isChecked());
        m_pointSource->setActive(m_activeCheckBox->isChecked());
        m_pointSource->build(true);
    }
    else if(m_reflection)
    {
        m_pointSource->setWavelength(m_wavelengthSpinBox->value());
        m_pointSource->setOrder(0, m_orderCheckBoxes[0]->isChecked());
        m_pointSource->setOrder(1, m_orderCheckBoxes[1]->isChecked());
        m_pointSource->setOrder(2, m_orderCheckBoxes[2]->isChecked());
        m_pointSource->setOrder(3, m_orderCheckBoxes[3]->isChecked());
        m_pointSource->setOrder(4, m_orderCheckBoxes[4]->isChecked());
        m_pointSource->setActive(m_activeCheckBox->isChecked());
        m_pointSource->build(false);
    }
    m_geometry = false;
    m_reflection = false;
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
    m_geometry = false;
    m_reflection = false;
    m_applyButton->setEnabled(false);
    m_cancelButton->setEnabled(false);
}

void PointSourceForm::changed()
{
    m_applyButton->setEnabled(true);
    m_cancelButton->setEnabled(true);
}
