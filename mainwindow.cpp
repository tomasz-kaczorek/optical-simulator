#include "mainwindow.h"
#include "dockabletabwidget.h"
#include "planemirror.h"
#include "planemirrortab.h"
#include "concavemirror.h"
#include "concavemirrortab.h"
#include "diffractiongrating.h"
#include "diffractiongratingtab.h"
#include "lightsource.h"
#include "lightsourcetab.h"
#include "ray.h"
#include "settings.h"
#include "absorber.h"
#include <QIcon>
#include <QAction>
#include <QToolBar>
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QSettings>
#include <QCloseEvent>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    readSettings();
    buildToolbar();
    m_scene = new QGraphicsScene(0, 0, 2000, 2000, this);
    m_scene->setBackgroundBrush(QBrush(Qt::lightGray));
    m_reflectors.append(new Absorber(Settings::minX, Settings::minY, Settings::minX, Settings::maxY));
    m_reflectors.append(new Absorber(Settings::minX, Settings::maxY, Settings::maxX, Settings::maxY));
    m_reflectors.append(new Absorber(Settings::maxX, Settings::maxY, Settings::maxX, Settings::minY));
    m_reflectors.append(new Absorber(Settings::maxX, Settings::minY, Settings::minX, Settings::minY));
    m_view = new QGraphicsView(m_scene, this);
    m_view->ensureVisible(0, 0, 0, 0);
    m_reflectorTabs = new DockableTabWidget(tr("Reflectors"), this);
    m_lightSourceTabs = new DockableTabWidget(tr("Light Sources"), this);
    addDockWidget(Qt::BottomDockWidgetArea, m_reflectorTabs);
    addDockWidget(Qt::BottomDockWidgetArea, m_lightSourceTabs);
    setCentralWidget(m_view);
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
    toolbar->addAction(QIcon(QPixmap("Icons/RemoveReflector.png")), "Remove Reflector", this, SLOT(removeReflector()));
    toolbar->addAction(QIcon(QPixmap("Icons/RemoveLightSource.png")), "Remove Light Source", this, SLOT(removeLightSource()));
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
        Settings::itemPenWidth = settings.value("itemPenWidth", 0.0).toDouble();
        Settings::itemNormalLength = settings.value("itemNormalLength", 5.0).toDouble();
        Settings::rayPenWidth = settings.value("rayPenWidth", 0.0).toDouble();
        Settings::outlineWidth = settings.value("outlineWidth", 10.0).toDouble();
    settings.endGroup();
}

QStringList MainWindow::getNames()
{
    return m_reflectorTabs->getNames();
}

Reflector *MainWindow::getReflector(int index)
{
    return m_reflectors.at(index);
}

QList<Reflector *> const &MainWindow::getReflectors()
{
    return m_reflectors;
}

void MainWindow::addPlaneMirror()
{
    static unsigned int counter = 0;
    PlaneMirror *planeMirror = new PlaneMirror();
    PlaneMirrorTab *planeMirrorTab = new PlaneMirrorTab(planeMirror, this);
    m_scene->addItem(planeMirror);
    m_reflectors.push_back(planeMirror);
    m_reflectorTabs->addTab(planeMirrorTab, tr("Plane Mirror #")+QString::number(++counter));
    connect(planeMirrorTab, SIGNAL(newLabel(QWidget*,QString)), m_reflectorTabs, SLOT(newLabel(QWidget*,QString)));
}

void MainWindow::addConcaveMirror()
{
    static unsigned int counter = 0;
    ConcaveMirror *concaveMirror = new ConcaveMirror();
    ConcaveMirrorTab *concaveMirrorTab = new ConcaveMirrorTab(concaveMirror, this);
    m_scene->addItem(concaveMirror);
    m_reflectors.push_back(concaveMirror);
    m_reflectorTabs->addTab(concaveMirrorTab, tr("Concave Mirror #")+QString::number(++counter));
    connect(concaveMirrorTab, SIGNAL(newLabel(QWidget*,QString)), m_reflectorTabs, SLOT(newLabel(QWidget*,QString)));
}

void MainWindow::addDiffractionGrating()
{
    static unsigned int counter = 0;
    DiffractionGrating *diffractionGrating = new DiffractionGrating();
    DiffractionGratingTab *diffractionGratingTab = new DiffractionGratingTab(diffractionGrating, this);
    m_scene->addItem(diffractionGrating);
    m_reflectors.push_back(diffractionGrating);
    m_reflectorTabs->addTab(diffractionGratingTab, tr("Diffraction Grating #")+QString::number(++counter));
    connect(diffractionGratingTab, SIGNAL(newLabel(QWidget*,QString)), m_reflectorTabs, SLOT(newLabel(QWidget*,QString)));
}

void MainWindow::removeReflector()
{
    int index = m_reflectorTabs->removeCurrentTab();
    if(index >= 0)
    {
        Reflector *reflector = m_reflectors.takeAt(index);
        m_scene->removeItem(reflector);
        delete(reflector);
    }
}

void MainWindow::addLightSource()
{
    static unsigned int counter = 0;
    LightSource *lightSource = new LightSource(&m_reflectors);
    LightSourceTab *lightSourceTab = new LightSourceTab(lightSource, this);
    m_scene->addItem(lightSource);
    m_lightSources.push_back(lightSource);
    m_lightSourceTabs->addTab(lightSourceTab, tr("Light Source #")+QString::number(++counter));
    connect(lightSourceTab, SIGNAL(newLabel(QWidget*,QString)), m_lightSourceTabs, SLOT(newLabel(QWidget*,QString)));
}

void MainWindow::removeLightSource()
{
    int index = m_lightSourceTabs->removeCurrentTab();
    if(index >= 0)
    {
        LightSource *lightSource = m_lightSources.takeAt(index);
        m_scene->removeItem(lightSource);
        delete(lightSource);
    }
}

void MainWindow::recalculate()
{
    foreach(LightSource *lightSource, m_lightSources)
    {
        lightSource->plotRays();
    }
}
