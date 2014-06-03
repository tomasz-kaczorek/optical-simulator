#ifndef DOCKABLETABWIDGET_H
#define DOCKABLETABWIDGET_H

#include <QDockWidget>

class QTabWidget;

class DockableTabWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit DockableTabWidget(const QString &title, QWidget *parent = 0);
    void addTab(QWidget *page, const QString &label);
    int removeCurrentTab();
    QStringList getNames();
private:
    QTabWidget *m_tabs;
public slots:
    void newLabel(QWidget *w, const QString &label);
};

#endif // DOCKABLETABWIDGET_H
