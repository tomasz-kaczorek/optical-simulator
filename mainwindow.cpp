#include "mainwindow.h"

#include "concavemirrorform.h"
#include "diffractiongratingform.h"
#include "pointsourceform.h"
#include "opticaldevicetabwidget.h"
#include "opticalsystem.h"
#include "planemirrorform.h"
#include "settings.h"

#include <QIcon>
#include <QAction>
#include <QToolBar>
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QSettings>
#include <QCloseEvent>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QDockWidget>


MainWindow::MainWindow(QWidget * parent) :
    QMainWindow(parent),
    m_system(nullptr)
{
    readSettings();
    buildToolbar();

    m_system = new OpticalSystem(this);

}

MainWindow::~MainWindow()
{
    writeSettings();
}

void MainWindow::buildToolbar()
{
    QToolBar *toolbar = addToolBar("Main Toolbar");
    toolbar->setMovable(false);
    toolbar->addAction("Add Plane Mirror", this, SLOT(addPlaneMirror()));
    toolbar->addAction("Add Concave Mirror", this, SLOT(addConcaveMirror()));
    toolbar->addAction("Add Diffraction Grating", this, SLOT(addDiffractionGrating()));
    toolbar->addAction("Add Light Source", this, SLOT(addLightSource()));
    toolbar->addSeparator();
    toolbar->addAction("Remove Reflector", this, SLOT(removeReflector()));
    toolbar->addAction("Remove Light Source", this, SLOT(removeLightSource()));
    toolbar->addSeparator();
    toolbar->addAction("New System", this, SLOT(newSystem()));
    toolbar->addAction("Close System", this, SLOT(closeSystem()));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    closeSystem();
    writeSettings();
    event->accept();
}

void MainWindow::writeSettings()
{
    QSettings settings("PW", "Optical Simulator");

    settings.beginGroup("MainWindow");
        settings.setValue("size", size());
        settings.setValue("pos", pos());
        settings.setValue("fullScreen", isFullScreen());
    settings.endGroup();
    settings.beginGroup("Drawing");
        settings.setValue("PrimaryColor", Settings::primaryColor.name());
        settings.setValue("SecondaryColor", Settings::secondaryColor.name());
        settings.setValue("BackgroundColor", Settings::backgroundColor.name());
        settings.setValue("DeviceThickness", Settings::deviceThickness);
        settings.setValue("Normals", Settings::normals);
        settings.setValue("Labels", Settings::labels);
    settings.endGroup();
}

void MainWindow::readSettings()
{
    QSettings settings("PW", "Optical Simulator");

    settings.beginGroup("MainWindow");
        resize(settings.value("Size", QSize(400, 400)).toSize());
        move(settings.value("Position", QPoint(200, 200)).toPoint());
        if(settings.value("Fullscreen", false).toBool()) showFullScreen();
    settings.endGroup();
    settings.beginGroup("Drawing");
        Settings::minX = 0;
        Settings::maxX = 2000;
        Settings::minY = 0;
        Settings::maxY = 2000;
        Settings::primaryColor = QColor(settings.value("PrimaryColor", "#FFFFFF").toString());
        Settings::secondaryColor = QColor(settings.value("SecondaryColor", "#7F7F7F").toString());
        Settings::backgroundColor = QColor(settings.value("BackgroundColor", "#000000").toString());
        Settings::deviceThickness = settings.value("DeviceThickness", 0.0).toDouble();
        Settings::normals = settings.value("Normals", true).toBool();
        Settings::labels = settings.value("Labels", true).toBool();
    settings.endGroup();
}

void MainWindow::addPlaneMirror()
{
    m_system->addPlaneMirror();
}

void MainWindow::addConcaveMirror()
{
    m_system->addConcaveMirror();
}

void MainWindow::addDiffractionGrating()
{
    m_system->addDiffractionGrating();
}

void MainWindow::addLightSource()
{
    m_system->addPointSource();
}

void MainWindow::removeReflector()
{
    m_system->removeReflector();
}

void MainWindow::removeLightSource()
{
    m_system->removeLightSource();
}

void MainWindow::newSystem()
{

}

void MainWindow::openSystem()
{

}

void MainWindow::closeSystem()
{

}
