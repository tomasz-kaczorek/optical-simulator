#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class OpticalDeviceTabWidget;
class QGraphicsView;
class DockableTabWidget;
class Reflector;
class LightSource;
class OpticalSystem;

class MainWindow : public QMainWindow
{
    Q_OBJECT    
public:
    MainWindow(QWidget * parent = 0);
    ~MainWindow();
protected:
    void closeEvent(QCloseEvent *event);
private:
    void buildToolbar();
    void writeSettings();
    void readSettings();
    OpticalSystem * m_system;
    QGraphicsView * m_view;
    QDockWidget * m_reflectorDockWidget;
    QDockWidget * m_lightSourceDockWidget;
public slots:
    void addPlaneMirror();
    void addConcaveMirror();
    void addDiffractionGrating();
    void addLightSource();
    void removeReflector();
    void removeLightSource();
    void newSystem();
    void openSystem();
    void closeSystem();
};

#endif // MAINWINDOW_H
