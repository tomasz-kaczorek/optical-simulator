#include "sizedialog.h"

#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPlastiqueStyle>
#include <QPushButton>
#include <QVBoxLayout>

SizeDialog::SizeDialog(QWidget *parent) :
    QDialog(parent)
{
    m_minXSpinBox = new QDoubleSpinBox();
    m_minXSpinBox->setRange(-2000.0, 2000.0);
    m_minXSpinBox->setValue(0.0);
    m_minXSpinBox->setSuffix(" mm");

    m_maxXSpinBox = new QDoubleSpinBox();
    m_maxXSpinBox->setRange(-2000.0, 2000.0);
    m_maxXSpinBox->setValue(1600.0);
    m_maxXSpinBox->setSuffix(" mm");

    m_minYSpinBox = new QDoubleSpinBox();
    m_minYSpinBox->setRange(-2000.0, 2000.0);
    m_minYSpinBox->setValue(0.0);
    m_minYSpinBox->setSuffix(" mm");

    m_maxYSpinBox = new QDoubleSpinBox();
    m_maxYSpinBox->setRange(-2000.0, 2000.0);
    m_maxYSpinBox->setValue(900.0);
    m_maxYSpinBox->setSuffix(" mm");

    QGroupBox * xGroupBox = new QGroupBox("Horizontal Coordinates");
    xGroupBox->setStyle(new QPlastiqueStyle());

    QHBoxLayout * xLayout = new QHBoxLayout();

    xLayout->addWidget(new QLabel("From "));
    xLayout->addWidget(m_minXSpinBox);
    xLayout->addWidget(new QLabel(" to "));
    xLayout->addWidget(m_maxXSpinBox);

    QGroupBox * yGroupBox = new QGroupBox("Vertical Coordinates");
    yGroupBox->setStyle(new QPlastiqueStyle());

    QHBoxLayout * yLayout = new QHBoxLayout();

    yLayout->addWidget(new QLabel("From "));
    yLayout->addWidget(m_minYSpinBox);
    yLayout->addWidget(new QLabel(" to "));
    yLayout->addWidget(m_maxYSpinBox);

    QPushButton * OKButton = new QPushButton("OK");
    connect(OKButton, SIGNAL(clicked()), this, SLOT(accept()));

    xGroupBox->setLayout(xLayout);

    yGroupBox->setLayout(yLayout);

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addWidget(xGroupBox);
    layout->addWidget(yGroupBox);
    layout->addWidget(OKButton);

    setLayout(layout);

    setWindowModality(Qt::WindowModal);

    show();
}

qreal SizeDialog::minX()
{
    return m_minXSpinBox->value();
}

qreal SizeDialog::maxX()
{
    return m_maxXSpinBox->value();
}

qreal SizeDialog::minY()
{
    return m_minYSpinBox->value();
}

qreal SizeDialog::maxY()
{
    return m_maxYSpinBox->value();
}
