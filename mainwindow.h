#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class OpticalSystem;

class QDockWidget;
class QToolBar;

class MainWindow : public QMainWindow
{
    Q_OBJECT    
public:
    MainWindow(QWidget * parent = 0);
    ~MainWindow();
public slots:
    void toggleFileToolBar(bool checked);
    void toggleDeviceToolBar(bool checked);
    void toggleZoomToolBar(bool checked);
    void toggleReflectorsDockWidget(bool checked);
    void toggleLightSourcesDockWidget(bool checked);
protected:
    void closeEvent(QCloseEvent *event);
private:
    void buildMenuBar();
    void buildToolBar();
    void writeSettings();
    void readSettings();
private:
    OpticalSystem * m_system;
    QToolBar * m_fileToolBar;
    QToolBar * m_deviceToolBar;
    QToolBar * m_zoomToolBar;
    QDockWidget * m_reflectorsDockWidget;
    QDockWidget * m_lightSourcesDockWidget;
};

#endif // MAINWINDOW_H
