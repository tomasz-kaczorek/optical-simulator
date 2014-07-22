#include "opticaldevicetabwidget.h"

#include "opticaldeviceform.h"

OpticalDeviceTabWidget::OpticalDeviceTabWidget(QWidget * parent) :
    QTabWidget(parent)
{
}

OpticalDeviceTabWidget::~OpticalDeviceTabWidget()
{
}

void OpticalDeviceTabWidget::addTab(OpticalDeviceForm * form)
{
    setCurrentIndex(QTabWidget::addTab(form, form->name()));
}

void OpticalDeviceTabWidget::removeCurrentTab()
{
    delete currentWidget();
}

void OpticalDeviceTabWidget::removeAllTabs()
{
    while(count() > 0)
    {
        delete currentWidget();
    }
}

void OpticalDeviceTabWidget::apply()
{
    OpticalDeviceForm * form = static_cast<OpticalDeviceForm *>(currentWidget());
    int index = currentIndex();
    setTabText(index, form->name());
    setTabIcon(index, QIcon());
}

void OpticalDeviceTabWidget::cancel()
{
    int index = currentIndex();
    setTabIcon(index, QIcon());
}

void OpticalDeviceTabWidget::changed()
{
    setTabIcon(currentIndex(), QIcon("Icons/SaveIcon.png"));
}
