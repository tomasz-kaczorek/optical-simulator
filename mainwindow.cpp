#include "mainwindow.h"

#include "dockabletabwidget.h"
#include "planemirror.h"
#include "concavemirror.h"
#include "diffractiongrating.h"
#include "diffractiongratingform.h"
#include "concavemirrorform.h"
#include "lightsource.h"
#include "ray.h"
#include "settings.h"
#include "opticalsystem.h"
#include "opticaldevicetabwidget.h"
#include "planemirrorform.h"
#include "lightsourceform.h"

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


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    readSettings();
    buildToolbar();

    m_system = new OpticalSystem(0.0, 0.0, 2000.0, 2000.0, this);
    m_view = new QGraphicsView(m_system, this);
    m_view->ensureVisible(Settings::minX, Settings::minY, 0.0, 0.0);

    m_reflectorDockWidget = new QDockWidget(tr("Reflectors"), this);
    m_reflectorTabs = new OpticalDeviceTabWidget(m_reflectorDockWidget);
    m_reflectorDockWidget->setWidget(m_reflectorTabs);

    m_lightSourceDockWidget = new QDockWidget(tr("Light Sources"), this);
    m_lightSourceTabs = new OpticalDeviceTabWidget(m_lightSourceDockWidget);
    m_lightSourceDockWidget->setWidget(m_lightSourceTabs);

    setCentralWidget(m_view);
    addDockWidget(Qt::BottomDockWidgetArea, m_reflectorDockWidget);
    addDockWidget(Qt::BottomDockWidgetArea, m_lightSourceDockWidget);
    show();
}

MainWindow::~MainWindow()
{
    writeSettings();
}

void MainWindow::buildToolbar()
{
    QToolBar *toolbar = addToolBar("Main Toolbar");
    toolbar->setMovable(false);
    toolbar->addAction(QIcon(QPixmap("Icons/AddPlaneMirror.png")), "Add Plane Mirror", this, SLOT(addPlaneMirror()));
    toolbar->addAction(QIcon(QPixmap("Icons/AddConcaveMirror.png")), "Add Concave Mirror", this, SLOT(addConcaveMirror()));
    toolbar->addAction(QIcon(QPixmap("Icons/AddDiffractionGrating.png")), "Add Diffraction Grating", this, SLOT(addDiffractionGrating()));
    toolbar->addAction(QIcon(QPixmap("Icons/AddLightSource.png")), "Add Light Source", this, SLOT(addLightSource()));
    toolbar->addSeparator();
    toolbar->addAction(QIcon(QPixmap("Icons/RemoveLightSource.png")), "Draw", this, SLOT(recalculate()));
}

void MainWindow::closeEvent(QCloseEvent *event)
 {
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
        settings.setValue("minAngle", Settings::minAngle);
        settings.setValue("maxAngle", Settings::maxAngle);
        settings.setValue("minRadius", Settings::minRadius);
        settings.setValue("maxRadius", Settings::maxRadius);
        settings.setValue("minDensity", Settings::minDensity);
        settings.setValue("maxDensity", Settings::maxDensity);
        settings.setValue("minBlazingAngle", Settings::minBlazingAngle);
        settings.setValue("maxBlazingAngle", Settings::maxBlazingAngle);
        settings.setValue("minWavelength", Settings::minWavelength);
        settings.setValue("maxWavelength", Settings::maxWavelength);
        settings.setValue("minQuantity", Settings::minQuantity);
        settings.setValue("maxQuantity", Settings::maxQuantity);
        settings.setValue("decimals", Settings::decimals);
        settings.setValue("allowedRecursionDepth", Settings::allowedRecursionDepth);
        settings.setValue("itemPenWidth", Settings::itemPenWidth);
        settings.setValue("itemNormalLength", Settings::itemNormalLength);
        settings.setValue("rayPenWidth", Settings::rayPenWidth);
        settings.setValue("outlineWidth", Settings::outlineWidth);
    settings.endGroup();
}

void MainWindow::readSettings()
{
    QSettings settings("PW", "Optical Simulator");

    settings.beginGroup("MainWindow");
        resize(settings.value("size", QSize(400, 400)).toSize());
        move(settings.value("pos", QPoint(200, 200)).toPoint());
        if(settings.value("fullScreen", false).toBool()) showFullScreen();
        Settings::minX = 0;
        Settings::maxX = 2000;
        Settings::minY = 0;
        Settings::maxY = 2000;
        Settings::minAngle = settings.value("minAngle", -360.0).toDouble();
        Settings::maxAngle = settings.value("maxAngle", 360.0).toDouble();
        Settings::minRadius = settings.value("minRadius", 0.0).toDouble();
        Settings::maxRadius = settings.value("maxRadius", 1000.0).toDouble();
        Settings::minFocalLength = Settings::minRadius / 2.0;
        Settings::maxFocalLength = Settings::maxRadius / 2.0;
        Settings::minDensity = settings.value("minDensity", 10.0).toDouble();
        Settings::maxDensity = settings.value("maxDensity", 10000.0).toDouble();
        Settings::minBlazingAngle = settings.value("minBlazingAngle", -90.0).toDouble();
        Settings::maxBlazingAngle = settings.value("maxBlazingAngle", 90.0).toDouble();
        Settings::minWavelength = settings.value("minWavelength", 380.0).toDouble();
        Settings::maxWavelength = settings.value("maxWavelength", 780.0).toDouble();
        Settings::minQuantity = settings.value("minQuantity", 0).toInt();
        Settings::maxQuantity = settings.value("maxQuantity", 100).toInt();
        Settings::decimals = settings.value("decimals", 4).toDouble();
        Settings::epsilon = 1;
        for(int i = 0; i < 4; i++) Settings::epsilon /= 10;
        Settings::allowedRecursionDepth = settings.value("allowedRecursionDepth", 20).toInt();
        Settings::itemPenWidth = settings.value("itemPenWidth", 0.0).toDouble();
        Settings::itemNormalLength = settings.value("itemNormalLength", 5.0).toDouble();
        Settings::rayPenWidth = settings.value("rayPenWidth", 0.0).toDouble();
        Settings::outlineWidth = settings.value("outlineWidth", 10.0).toDouble();
    settings.endGroup();
}

void MainWindow::addPlaneMirror()
{
    PlaneMirror *planeMirror = new PlaneMirror();
    PlaneMirrorForm *planeMirrorForm = new PlaneMirrorForm(planeMirror, m_reflectorTabs);
    m_system->addReflector(planeMirror);
    m_reflectorTabs->addTab(planeMirrorForm);
}

void MainWindow::addConcaveMirror()
{
    ConcaveMirror *concaveMirror = new ConcaveMirror();
    ConcaveMirrorForm *concaveMirrorForm = new ConcaveMirrorForm(concaveMirror, m_reflectorTabs);
    m_system->addReflector(concaveMirror);
    m_reflectorTabs->addTab(concaveMirrorForm);
}

void MainWindow::addDiffractionGrating()
{
    DiffractionGrating *diffractionGrating = new DiffractionGrating();
    DiffractionGratingForm *diffractionGratingForm = new DiffractionGratingForm(diffractionGrating, m_reflectorTabs);
    m_system->addReflector(diffractionGrating);
    m_reflectorTabs->addTab(diffractionGratingForm);
}

void MainWindow::addLightSource()
{
    LightSource *lightSource = new LightSource();
    LightSourceForm *lightSourceForm = new LightSourceForm(lightSource, m_lightSourceTabs);
    m_system->addLightSource(lightSource);
    m_lightSourceTabs->addTab(lightSourceForm);
}

void MainWindow::recalculate()
{
    foreach(LightSource *lightSource, m_lightSources)
    {
        //lightSource->plotRays();
    }
}
