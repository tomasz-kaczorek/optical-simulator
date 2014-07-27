#include "aimdialog.h"

#include <opticaldevice.h>
#include <opticalsystem.h>
#include <reflector.h>

#include <QComboBox>
#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPlastiqueStyle>
#include <QPushButton>
#include <QStringList>
#include <QVBoxLayout>

AimDialog::AimDialog(OpticalDevice * opticalDevice, QWidget * parent) :
    QDialog(parent),
    m_reflectors(opticalDevice->system()->reflectors())
{
    QStringList points;
    points.append("");
    points.append("Left Edge");
    points.append("Center");
    points.append("Right Edge");

    QStringList names;
    const int size = m_reflectors.size();
    names.append("");
    for(int i = 4; i < size; i++) names.append(m_reflectors.at(i)->name());

    m_beginAnglePointComboBox = new QComboBox();
    m_beginAnglePointComboBox->addItems(points);

    m_beginAngleReflectorComboBox = new QComboBox();
    m_beginAngleReflectorComboBox->addItems(names);

    m_endAnglePointComboBox = new QComboBox();
    m_endAnglePointComboBox->addItems(points);

    m_endAngleReflectorComboBox = new QComboBox();
    m_endAngleReflectorComboBox->addItems(names);

    QGroupBox * beginAngleGroupBox = new QGroupBox("Angle #1");
    beginAngleGroupBox->setStyle(new QPlastiqueStyle());

    QHBoxLayout * beginAngleLayout = new QHBoxLayout();

    beginAngleLayout->addWidget(new QLabel("Aim at "));
    beginAngleLayout->addWidget(m_beginAnglePointComboBox);
    beginAngleLayout->addWidget(new QLabel(" of "));
    beginAngleLayout->addWidget(m_beginAngleReflectorComboBox);

    QGroupBox * endAngleGroupBox = new QGroupBox("Angle #2");
    endAngleGroupBox->setStyle(new QPlastiqueStyle());

    QHBoxLayout * endAngleLayout = new QHBoxLayout();

    endAngleLayout->addWidget(new QLabel("Aim at "));
    endAngleLayout->addWidget(m_endAnglePointComboBox);
    endAngleLayout->addWidget(new QLabel(" of "));
    endAngleLayout->addWidget(m_endAngleReflectorComboBox);

    QPushButton * OKButton = new QPushButton("OK");
    connect(OKButton, SIGNAL(clicked()), this, SLOT(accept()));

    beginAngleGroupBox->setLayout(beginAngleLayout);

    endAngleGroupBox->setLayout(endAngleLayout);

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addWidget(beginAngleGroupBox);
    layout->addWidget(endAngleGroupBox);
    layout->addWidget(OKButton);

    setLayout(layout);

    setWindowModality(Qt::WindowModal);

    show();
}

bool AimDialog::hasBeginPoint()
{
    return m_beginAngleReflectorComboBox->currentIndex() > 0 && m_beginAnglePointComboBox->currentIndex() > 0;
}

QPointF AimDialog::beginPoint()
{
    Reflector * reflector = m_reflectors.at(m_beginAngleReflectorComboBox->currentIndex() + 3);
    switch(m_beginAnglePointComboBox->currentIndex())
    {
        case 1: return reflector->leftEdge();
        case 2: return reflector->pos();
        case 3: return reflector->rightEdge();
        default: return QPointF();
    }
}

bool AimDialog::hasEndPoint()
{
    return m_endAngleReflectorComboBox->currentIndex() > 0 && m_endAnglePointComboBox->currentIndex() > 0;
}

QPointF AimDialog::endPoint()
{
    Reflector * reflector = m_reflectors.at(m_endAngleReflectorComboBox->currentIndex() + 3);
    switch(m_endAnglePointComboBox->currentIndex())
    {
        case 1: return reflector->leftEdge();
        case 2: return reflector->pos();
        case 3: return reflector->rightEdge();
        default: return QPointF();
    }
}
