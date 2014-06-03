#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QGraphicsScene;
class QGraphicsView;
class DockableTabWidget;
class Reflector;
class LightSource;

class MainWindow : public QMainWindow
{
    Q_OBJECT    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QStringList getNames();
    Reflector *getReflector(int index);
    QList<Reflector *> const &getReflectors();
protected:
    void closeEvent(QCloseEvent *event);
private:
    void buildToolbar();
    void writeSettings();
    void readSettings();
    QGraphicsScene *m_scene;
    QGraphicsView *m_view;
    DockableTabWidget *m_reflectorTabs;
    DockableTabWidget *m_lightSourceTabs;
    QList<Reflector *> m_reflectors;
    QList<LightSource *> m_lightSources;
public slots:
    void addPlaneMirror();
    void addConcaveMirror();
    void addDiffractionGrating();
    void addLightSource();
    void removeReflector();
    void removeLightSource();
    void recalculate();
};

#endif // MAINWINDOW_H
