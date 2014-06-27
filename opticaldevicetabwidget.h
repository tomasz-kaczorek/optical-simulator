#ifndef OPTICALDEVICETABWIDGET_H
#define OPTICALDEVICETABWIDGET_H

#include <QWidget>

class OpticalDeviceForm;

class QGridLayout;
class QPushButton;
class QTabWidget;

class OpticalDeviceTabWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OpticalDeviceTabWidget(QWidget *parent = 0);
    void addTab(OpticalDeviceForm *page);
private:
    QGridLayout *m_layout;
    QTabWidget *m_tabs;
    QPushButton *m_applyButton;
    QPushButton *m_cancelButton;
    QPushButton *m_removeButton;
public slots:
    void apply();
    void cancel();
    void remove();
};

#endif // OPTICALDEVICETABWIDGET_H
