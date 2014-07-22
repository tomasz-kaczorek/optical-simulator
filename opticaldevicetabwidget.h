#ifndef OPTICALDEVICETABWIDGET_H
#define OPTICALDEVICETABWIDGET_H

#include <QTabWidget>

class OpticalDeviceForm;

class QPushButton;

class OpticalDeviceTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit OpticalDeviceTabWidget(QWidget * parent = 0);
    ~OpticalDeviceTabWidget();

    void addTab(OpticalDeviceForm * form);
    void removeCurrentTab();
    void removeAllTabs();
private slots:
    void apply();
    void cancel();
    void changed();
private:
    int	addTab(QWidget * page, QString const & label);
    int	addTab(QWidget * page, QIcon const & icon, QString const & label);
};

#endif // OPTICALDEVICETABWIDGET_H
