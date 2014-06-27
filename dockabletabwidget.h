#ifndef DOCKABLETABWIDGET_H
#define DOCKABLETABWIDGET_H

#include <QDockWidget>

class QGridLayout;
class QPushButton;
class QTabWidget;

class DockableTabWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit DockableTabWidget(QString const &title, QWidget *parent = 0);
    void addTab(QWidget *page, const QString &label);
private:
    class TabWidget : public QWidget
    {
    public:
        TabWidget(QWidget *parent = 0);
        QGridLayout *m_layout;
        QTabWidget *m_tabs;
        QPushButton *m_applyButton;
        QPushButton *m_cancelButton;
        QPushButton *m_removeButton;
    };
    TabWidget *m_widget;
public slots:
    void newLabel(QString const &label);
};

#endif // DOCKABLETABWIDGET_H
