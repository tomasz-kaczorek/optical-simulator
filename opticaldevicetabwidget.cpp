#include "opticaldevicetabwidget.h"

#include "opticaldeviceform.h"

#include <QGridLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QTabWidget>

OpticalDeviceTabWidget::OpticalDeviceTabWidget(QWidget *parent) :
    QWidget(parent)
{
    m_layout = new QGridLayout(this);

    m_tabs = new QTabWidget();

    m_applyButton = new QPushButton("Apply");
    m_applyButton->setEnabled(false);
    m_applyButton->setAutoDefault(true);

    m_cancelButton = new QPushButton("Cancel");
    m_cancelButton->setEnabled(false);
    m_cancelButton->setAutoDefault(true);

    m_removeButton = new QPushButton("Remove");
    m_removeButton->setEnabled(false);
    m_removeButton->setAutoDefault(true);

    m_layout->addWidget(m_tabs, 0, 0, 1, 3);
    m_layout->addWidget(m_applyButton, 1, 0);
    m_layout->addWidget(m_cancelButton, 1, 1);
    m_layout->addWidget(m_removeButton, 1, 2);

    connect(m_applyButton, SIGNAL(clicked()), this, SLOT(apply()));
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(m_removeButton, SIGNAL(clicked()), this, SLOT(remove()));
}

void OpticalDeviceTabWidget::addTab(OpticalDeviceForm *page)
{
    m_tabs->addTab(page, page->name());
    m_tabs->setCurrentWidget(page);
    if(m_tabs->count() == 1)
    {
        m_applyButton->setEnabled(true);
        m_cancelButton->setEnabled(true);
        m_removeButton->setEnabled(true);
    }
}

void OpticalDeviceTabWidget::apply()
{
    unsigned int index = m_tabs->currentIndex();
    OpticalDeviceForm *page = static_cast<OpticalDeviceForm *>(m_tabs->widget(index));
    m_tabs->setTabText(index, page->name());
    page->apply();
}

void OpticalDeviceTabWidget::cancel()
{
    static_cast<OpticalDeviceForm *>(m_tabs->currentWidget())->cancel();
}

void OpticalDeviceTabWidget::remove()
{
    if(m_tabs->count() == 1)
    {
        m_applyButton->setEnabled(false);
        m_cancelButton->setEnabled(false);
        m_removeButton->setEnabled(false);
    }
    QWidget *page = m_tabs->currentWidget();
    m_tabs->removeTab(m_tabs->currentIndex());
    delete page;
}
