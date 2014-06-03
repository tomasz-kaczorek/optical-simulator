#include "dockabletabwidget.h"
#include <QTabWidget>

DockableTabWidget::DockableTabWidget(const QString &title, QWidget *parent) :
    QDockWidget(title, parent)
{
    m_tabs = new QTabWidget();
    setWidget(m_tabs);
}

void DockableTabWidget::addTab(QWidget *page, const QString &label)
{
    connect(page, SIGNAL(newLabel(QWidget *, const QString &)), this, SLOT(newLabel(QWidget *, const QString &)));
    m_tabs->addTab(page, label);
    m_tabs->setCurrentWidget(page);
}

int DockableTabWidget::removeCurrentTab()
{
    int index = m_tabs->currentIndex();
    m_tabs->removeTab(index);
    return index;
}

QStringList DockableTabWidget::getNames()
{
    QStringList names;
    for(int i = 0; i < m_tabs->count(); ++i)
        names.append(m_tabs->tabText(i));
    return names;
}

void DockableTabWidget::newLabel(QWidget *w, const QString &label)
{
    m_tabs->setTabText(m_tabs->indexOf(w), label);
}


