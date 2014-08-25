#include "zoomwidget.h"

#include <QPushButton>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QMenu>

ZoomWidget::ZoomWidget(QWidget *parent) :
    QWidget(parent),
    m_values{25, 50, 75, 100, 125, 150, 175, 200, 250, 300, 400, 500, 750, 1000}
{
    m_zoomSpinBox = new QSpinBox();
    m_zoomSpinBox->setRange(25, 1000);
    m_zoomSpinBox->setValue(100);
    m_zoomSpinBox->setSuffix("%");
    m_zoomSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
    connect(m_zoomSpinBox, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));

    QMenu * menu = new QMenu(this);
    QAction * action;
    for(int i = 0; i < 14; ++i)
    {
        action = new QAction(QString::number(m_values[i]) + '%', menu);
        action->setData(i);
        menu->addAction(action);
    }
    connect(menu, SIGNAL(triggered(QAction*)), this, SLOT(menu(QAction*)));

    m_zoomButton = new QPushButton();
    m_zoomButton->setFixedWidth(23);
    m_zoomButton->setMenu(menu);

    QHBoxLayout * layout = new QHBoxLayout();
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_zoomSpinBox);
    layout->addWidget(m_zoomButton);
    setLayout(layout);
}

void ZoomWidget::menu(QAction * action)
{
    m_zoomSpinBox->setValue(m_values[action->data().toInt()]);
}

void ZoomWidget::stepUp()
{
    for(int i = 1; i < 14; ++i)
        if(m_zoomSpinBox->value() < m_values[i])
        {
            m_zoomSpinBox->setValue(m_values[i]);
            break;
        }
}

void ZoomWidget::stepDown()
{
    for(int i = 12; i >= 0; --i)
        if(m_zoomSpinBox->value() > m_values[i])
        {
            m_zoomSpinBox->setValue(m_values[i]);
            break;
        }
}
