#include "aimdialog.h"
#include <QVBoxLayout>
#include <QComboBox>
#include <QGroupBox>
#include <QRadioButton>
#include <QPlastiqueStyle>
#include <QPushButton>
#include "dockabletabwidget.h"

AimDialog::AimDialog(QStringList names, QWidget *parent) :
    QDialog(parent)
{
    m_layout = new QVBoxLayout(this);
    m_reflectorsComboBox = new QComboBox(this);
    m_reflectorsComboBox->addItems(names);
    m_groupBox = new QGroupBox(tr("aim at:"), this);
    m_groupBox->setStyle(new QPlastiqueStyle());
    m_groupBoxLayout = new QVBoxLayout(m_groupBox);
    m_aimCenterRadioButton = new QRadioButton(tr("center"), m_groupBox);
    m_aimCenterRadioButton->setChecked(true);
    m_aimLeftRadioButton = new QRadioButton(tr("left edge"), m_groupBox);
    m_aimRightRadioButton = new QRadioButton(tr("right edge"), m_groupBox);
    m_aimBothRadioButton = new QRadioButton(tr("both edges"), m_groupBox);
    m_okPushButton = new QPushButton(tr("OK"), this);

    m_layout->addWidget(m_reflectorsComboBox);
    m_groupBoxLayout->addWidget(m_aimCenterRadioButton);
    m_groupBoxLayout->addWidget(m_aimLeftRadioButton);
    m_groupBoxLayout->addWidget(m_aimRightRadioButton);
    m_groupBoxLayout->addWidget(m_aimBothRadioButton);
    m_layout->addWidget(m_groupBox);
    m_layout->addWidget(m_okPushButton);

    connect(m_okPushButton, SIGNAL(clicked()), this, SLOT(accept()));

    setWindowModality(Qt::WindowModal);
    show();
}

int AimDialog::getIndex()
{
    return m_reflectorsComboBox->currentIndex();
}

int AimDialog::getChoice()
{
    if(m_aimCenterRadioButton->isChecked()) return 0;
    if(m_aimLeftRadioButton->isChecked()) return 1;
    if(m_aimRightRadioButton->isChecked()) return 2;
    if(m_aimBothRadioButton->isChecked()) return 3;
    return -1;
}
