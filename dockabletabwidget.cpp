#include "dockabletabwidget.h"
#include <QTabWidget>

#include <QGridLayout>
#include <QPushButton>

DockableTabWidget::DockableTabWidget(QString const &title, QWidget *parent) :
    QDockWidget(title, parent)
{
    m_widget = new TabWidget(this);
    setWidget(m_widget);
}

void DockableTabWidget::addTab(QWidget *page, QString const &label)
{
    m_widget->m_tabs->addTab(page, label);
    m_widget->m_tabs->setCurrentWidget(page);
    //first tab was added
    if(m_widget->m_tabs->count() == 1)
    {
        m_widget->m_applyButton->setEnabled(true);
        m_widget->m_cancelButton->setEnabled(true);
        m_widget->m_removeButton->setEnabled(true);
    }
}

void DockableTabWidget::newLabel(QString const &label)
{
    m_widget->m_tabs->setTabText(m_widget->m_tabs->currentIndex(), label);
}

DockableTabWidget::TabWidget::TabWidget(QWidget *parent) :
    QWidget(parent)
{
    m_layout = new QGridLayout(this);

    m_tabs = new QTabWidget(this);

    m_applyButton = new QPushButton("Apply", this);
    m_applyButton->setEnabled(false);
    m_applyButton->setAutoDefault(true);

    m_cancelButton = new QPushButton("Cancel", this);
    m_cancelButton->setEnabled(false);
    m_cancelButton->setAutoDefault(true);

    m_removeButton = new QPushButton("Remove", this);
    m_removeButton->setEnabled(false);
    m_removeButton->setAutoDefault(true);

    m_layout->addWidget(m_tabs, 0, 0, 1, 3);
    m_layout->addWidget(m_applyButton, 1, 0);
    m_layout->addWidget(m_cancelButton, 1, 1);
    m_layout->addWidget(m_removeButton, 1, 2);
}
