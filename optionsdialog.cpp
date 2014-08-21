#include "optionsdialog.h"

#include "settings.h"

#include <QCheckBox>
#include <QColor>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QPainter>
#include <QPushButton>

#include <QToolButton>
#include <QColorDialog>

OptionsDialog::OptionsDialog(QWidget *parent) :
    QDialog(parent),
    m_primaryColor(Settings::primaryColor),
    m_secondaryColor(Settings::secondaryColor),
    m_backgroundColor(Settings::backgroundColor)
{
    m_normalsCheckBox = new QCheckBox("ON");
    m_normalsCheckBox->setCheckState(Settings::normals == true ? Qt::Checked : Qt::Unchecked);
    connect(m_normalsCheckBox, SIGNAL(stateChanged(int)), this, SLOT(normalsChanged(int)));


    m_labelsCheckBox = new QCheckBox("ON");
    m_labelsCheckBox->setCheckState(Settings::labels == true ? Qt::Checked : Qt::Unchecked);
    connect(m_labelsCheckBox, SIGNAL(stateChanged(int)), this, SLOT(labelsChanged(int)));


    QStringList thickness;
    thickness.append("0 px");
    thickness.append("1 px");
    thickness.append("2 px");
    thickness.append("3 px");

    m_thicknessComboBox = new QComboBox();
    m_thicknessComboBox->addItems(thickness);
    m_thicknessComboBox->setCurrentIndex(Settings::deviceThickness);

    m_primaryColorButton = new QToolButton();
    m_primaryColorButton->setIcon(icon(Settings::primaryColor));
    connect(m_primaryColorButton, SIGNAL(clicked()), this, SLOT(primaryColorClicked()));

    m_secondaryColorButton = new QToolButton();
    m_secondaryColorButton->setIcon(icon(Settings::secondaryColor));
    connect(m_secondaryColorButton, SIGNAL(clicked()), this, SLOT(secondaryColorClicked()));

    m_backgroundColorButton = new QToolButton();
    m_backgroundColorButton->setIcon(icon(Settings::backgroundColor));
    connect(m_backgroundColorButton, SIGNAL(clicked()), this, SLOT(backgroundColorClicked()));

    QPushButton * OKButton = new QPushButton("OK");
    connect(OKButton, SIGNAL(clicked()), this, SLOT(accept()));

    QGridLayout * layout = new QGridLayout();

    layout->addWidget(new QLabel("Normals:"), 0, 0);
    layout->addWidget(m_normalsCheckBox, 0, 1);
    layout->addWidget(new QLabel("Primary Color:"), 0, 2);
    layout->addWidget(m_primaryColorButton, 0, 3);
    layout->addWidget(new QLabel("Labels:"), 1, 0);
    layout->addWidget(m_labelsCheckBox, 1, 1);
    layout->addWidget(new QLabel("Secondary Color:"), 1, 2);
    layout->addWidget(m_secondaryColorButton, 1, 3);
    layout->addWidget(new QLabel("Pen Width:"), 2, 0);
    layout->addWidget(m_thicknessComboBox, 2, 1);
    layout->addWidget(new QLabel("Background Color:"), 2, 2);
    layout->addWidget(m_backgroundColorButton, 2, 3);
    layout->addWidget(OKButton, 3, 0, 1, 4);

    setLayout(layout);

    setWindowModality(Qt::WindowModal);

    show();
}

bool OptionsDialog::normals()
{
    return m_normalsCheckBox->checkState() == Qt::Checked;
}

bool OptionsDialog::labels()
{
    return m_labelsCheckBox->checkState() == Qt::Checked;
}

int OptionsDialog::deviceThickness()
{
    return m_thicknessComboBox->currentIndex();
}

QColor OptionsDialog::primaryColor()
{
    return m_primaryColor;
}

QColor OptionsDialog::secondaryColor()
{
    return m_secondaryColor;
}

QColor OptionsDialog::backgroundColor()
{
    return m_backgroundColor;
}

void OptionsDialog::normalsChanged(int state)
{
    if(state == Qt::Checked) m_normalsCheckBox->setText("ON");
    else m_normalsCheckBox->setText("OFF");
}

void OptionsDialog::labelsChanged(int state)
{
    if(state == Qt::Checked) m_labelsCheckBox->setText("ON");
    else m_labelsCheckBox->setText("OFF");
}

void OptionsDialog::primaryColorClicked()
{
    QColor color = QColorDialog::getColor(Settings::primaryColor, this, "Primary Color");
    if(color.isValid()) m_primaryColorButton->setIcon(icon(m_primaryColor = color));
}

void OptionsDialog::secondaryColorClicked()
{
    QColor color = QColorDialog::getColor(Settings::secondaryColor, this, "Secondary Color");
    if(color.isValid()) m_secondaryColorButton->setIcon(icon(m_secondaryColor = color));
}

void OptionsDialog::backgroundColorClicked()
{
    QColor color = QColorDialog::getColor(Settings::backgroundColor, this, "Background Color");
    if(color.isValid()) m_backgroundColorButton->setIcon(icon(m_backgroundColor = color));
}

QIcon OptionsDialog::icon(QColor color)
{
    QPixmap pixmap(16, 16);
    QPainter painter(&pixmap);
    painter.drawRect(0, 0, 15, 15);
    painter.fillRect(1, 1, 14, 14, color);
    return QIcon(pixmap);
}
