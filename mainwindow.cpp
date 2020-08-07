#include "mainwindow.h"

#include "opticalsystem.h"
#include "opticaldevicetabwidget.h"
#include "settings.h"
#include "zoomwidget.h"

#include <QCloseEvent>
#include <QDockWidget>
#include <QIcon>
#include <QMenuBar>
#include <QSettings>
#include <QToolBar>

MainWindow::MainWindow(QWidget * parent) :
    QMainWindow(parent),
    m_system(nullptr)
{
    readSettings();

    m_system = new OpticalSystem(this);
    m_reflectorsDockWidget = new QDockWidget("Reflectors", this);
    m_lightSourcesDockWidget = new QDockWidget("Light Sources", this);

    setCentralWidget(m_system);
    m_reflectorsDockWidget->setWidget(m_system->reflectorsTabs());
    m_lightSourcesDockWidget->setWidget(m_system->lightSourcesTabs());
    addDockWidget(Qt::BottomDockWidgetArea, m_reflectorsDockWidget);
    addDockWidget(Qt::BottomDockWidgetArea, m_lightSourcesDockWidget);

    buildToolBar();
    buildMenuBar();
}

MainWindow::~MainWindow()
{
    writeSettings();
}

void MainWindow::toggleFileToolBar(bool checked)
{
    m_fileToolBar->setVisible(checked);
}

void MainWindow::toggleDeviceToolBar(bool checked)
{
    m_deviceToolBar->setVisible(checked);
}

void MainWindow::toggleZoomToolBar(bool checked)
{
    m_zoomToolBar->setVisible(checked);
}

void MainWindow::toggleReflectorsDockWidget(bool checked)
{
    m_reflectorsDockWidget->setVisible(checked);
}

void MainWindow::toggleLightSourcesDockWidget(bool checked)
{
    m_lightSourcesDockWidget->setVisible(checked);
}

void MainWindow::buildMenuBar()
{
    QMenu * fileMenu = menuBar()->addMenu("File");
    QAction * newAction = new QAction(QIcon("Icons/New.png"), "New", this);
    connect(newAction, SIGNAL(triggered()), m_system, SLOT(newSystem()));
    QAction * openAction = new QAction(QIcon("Icons/Open.png"), "Open", this);
    connect(openAction, SIGNAL(triggered()), m_system, SLOT(openSystem()));
    QAction * saveAction = new QAction(QIcon("Icons/Save.png"), "Save", this);
    connect(saveAction, SIGNAL(triggered()), m_system, SLOT(saveSystem()));
    QAction * saveAsAction = new QAction(QIcon("Icons/SaveAs.png"), "Save As...", this);
    connect(saveAsAction, SIGNAL(triggered()), m_system, SLOT(saveSystemAs()));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);

    QMenu * deviceMenu = menuBar()->addMenu("Device");
    QAction * addPlaneMirrorAction = new QAction(QIcon("Icons/PlaneMirror.png"), "Add Plane Mirror", this);
    connect(addPlaneMirrorAction, SIGNAL(triggered()), m_system, SLOT(addPlaneMirror()));
    QAction * addConcaveMirrorAction = new QAction(QIcon("Icons/ConcaveMirror.png"), "Add Concave Mirror", this);
    connect(addConcaveMirrorAction, SIGNAL(triggered()), m_system, SLOT(addConcaveMirror()));
    QAction * addDiffractionGratingAction = new QAction(QIcon("Icons/DiffractionGrating.png"), "Add Diffraction Grating", this);
    connect(addDiffractionGratingAction, SIGNAL(triggered()), m_system, SLOT(addDiffractionGrating()));
    QAction * addSlitAction = new QAction(QIcon("Icons/Slit.png"), "Add Slit", this);
    connect(addSlitAction, SIGNAL(triggered()), m_system, SLOT(addSlit()));
    QAction * addPointSourceAction = new QAction(QIcon("Icons/PointSource.png"), "Add Point Source", this);
    connect(addPointSourceAction, SIGNAL(triggered()), m_system, SLOT(addPointSource()));
    QAction * removeReflectorAction = new QAction(QIcon("Icons/RemoveReflector.png"), "Remove Reflector", this);
    connect(removeReflectorAction, SIGNAL(triggered()), m_system, SLOT(removeReflector()));
    QAction * removeLightSourceAction = new QAction(QIcon("Icons/RemoveLightSource.png"), "Remove Light Source", this);
    connect(removeLightSourceAction, SIGNAL(triggered()), m_system, SLOT(removeLightSource()));
    deviceMenu->addAction(addPlaneMirrorAction);
    deviceMenu->addAction(addConcaveMirrorAction);
    deviceMenu->addAction(addDiffractionGratingAction);
    deviceMenu->addAction(addSlitAction);
    deviceMenu->addSeparator();
    deviceMenu->addAction(addPointSourceAction);
    deviceMenu->addSeparator();
    deviceMenu->addAction(removeReflectorAction);
    deviceMenu->addAction(removeLightSourceAction);

    QMenu * viewMenu = menuBar()->addMenu("View");
    QMenu * toolbarsMenu = new QMenu("Toolbars", this);
    QAction * fileAction = new QAction("File", this);
    fileAction->setCheckable(true);
    fileAction->setChecked(true);
    connect(fileAction, SIGNAL(triggered(bool)), this, SLOT(toggleFileToolBar(bool)));
    connect(m_fileToolBar, SIGNAL(visibilityChanged(bool)), fileAction, SLOT(setChecked(bool)));
    QAction * deviceAction = new QAction("Device", this);
    deviceAction->setCheckable(true);
    deviceAction->setChecked(true);
    connect(deviceAction, SIGNAL(triggered(bool)), this, SLOT(toggleDeviceToolBar(bool)));
    connect(m_deviceToolBar, SIGNAL(visibilityChanged(bool)), deviceAction, SLOT(setChecked(bool)));
    QAction * zoomAction = new QAction("Zoom", this);
    zoomAction->setCheckable(true);
    zoomAction->setChecked(true);
    connect(zoomAction, SIGNAL(triggered(bool)), this, SLOT(toggleZoomToolBar(bool)));
    connect(m_zoomToolBar, SIGNAL(visibilityChanged(bool)), zoomAction, SLOT(setChecked(bool)));
    QAction * reflectorsAction = new QAction("Reflectors", this);
    reflectorsAction->setCheckable(true);
    reflectorsAction->setChecked(true);
    connect(reflectorsAction, SIGNAL(triggered(bool)), this, SLOT(toggleReflectorsDockWidget(bool)));
    connect(m_reflectorsDockWidget, SIGNAL(visibilityChanged(bool)), reflectorsAction, SLOT(setChecked(bool)));
    QAction * lightSourcesAction = new QAction("Light Sources", this);
    lightSourcesAction->setCheckable(true);
    lightSourcesAction->setChecked(true);
    connect(lightSourcesAction, SIGNAL(triggered(bool)), this, SLOT(toggleLightSourcesDockWidget(bool)));
    connect(m_lightSourcesDockWidget, SIGNAL(visibilityChanged(bool)), lightSourcesAction, SLOT(setChecked(bool)));
    QAction * optionsAction = new QAction("Options...", this);
    connect(optionsAction, SIGNAL(triggered()), m_system, SLOT(options()));
    toolbarsMenu->addAction(fileAction);
    toolbarsMenu->addAction(deviceAction);
    toolbarsMenu->addAction(zoomAction);
    viewMenu->addMenu(toolbarsMenu);
    viewMenu->addSeparator();
    viewMenu->addAction(reflectorsAction);
    viewMenu->addAction(lightSourcesAction);
    viewMenu->addSeparator();
    viewMenu->addAction(optionsAction);
}

void MainWindow::buildToolBar()
{
    m_fileToolBar = addToolBar("File Tool Bar");
    m_fileToolBar->setMovable(true);
    QAction * newSystemAction = new QAction(QIcon("Icons/New.png"), "New", this);
    connect(newSystemAction, SIGNAL(triggered()), m_system, SLOT(newSystem()));
    QAction * openSystemAction = new QAction(QIcon("Icons/Open.png"), "Open", this);
    connect(openSystemAction, SIGNAL(triggered()), m_system, SLOT(openSystem()));
    QAction * saveSystemAction = new QAction(QIcon("Icons/Save.png"), "Save", this);
    connect(saveSystemAction, SIGNAL(triggered()), m_system, SLOT(saveSystem()));
    QAction * saveSystemAsAction = new QAction(QIcon("Icons/SaveAs.png"), QString::fromUtf8("Save As\u2026"), this);
    saveSystemAsAction->setIconText("AA");
    connect(saveSystemAsAction, SIGNAL(triggered()), m_system, SLOT(saveSystemAs()));
    m_fileToolBar->addAction(newSystemAction);
    m_fileToolBar->addAction(openSystemAction);
    m_fileToolBar->addAction(saveSystemAction);
    m_fileToolBar->addAction(saveSystemAsAction);

    m_deviceToolBar = addToolBar("Device Tool Bar");
    m_deviceToolBar->setMovable(true);
    QAction * addPlaneMirrorAction = new QAction(QIcon("Icons/PlaneMirror.png"), "Add Plane Mirror", this);
    connect(addPlaneMirrorAction, SIGNAL(triggered()), m_system, SLOT(addPlaneMirror()));
    QAction * addConcaveMirrorAction = new QAction(QIcon("Icons/ConcaveMirror.png"), "Add Concave Mirror", this);
    connect(addConcaveMirrorAction, SIGNAL(triggered()), m_system, SLOT(addConcaveMirror()));
    QAction * addDiffractionGratingAction = new QAction(QIcon("Icons/DiffractionGrating.png"), "Add Diffraction Grating", this);
    connect(addDiffractionGratingAction, SIGNAL(triggered()), m_system, SLOT(addDiffractionGrating()));
    QAction * addSlitAction = new QAction(QIcon("Icons/Slit.png"), "Add Slit", this);
    connect(addSlitAction, SIGNAL(triggered()), m_system, SLOT(addSlit()));
    QAction * addPointSourceAction = new QAction(QIcon("Icons/PointSource.png"), "Add Point Source", this);
    connect(addPointSourceAction, SIGNAL(triggered()), m_system, SLOT(addPointSource()));
    QAction * removeReflectorAction = new QAction(QIcon("Icons/RemoveReflector.png"), "Remove Reflector", this);
    connect(removeReflectorAction, SIGNAL(triggered()), m_system, SLOT(removeReflector()));
    QAction * removeLightSourceAction = new QAction(QIcon("Icons/RemoveLightSource.png"), "Remove Light Source", this);
    connect(removeLightSourceAction, SIGNAL(triggered()), m_system, SLOT(removeLightSource()));
    m_deviceToolBar->addAction(addPlaneMirrorAction);
    m_deviceToolBar->addAction(addConcaveMirrorAction);
    m_deviceToolBar->addAction(addDiffractionGratingAction);
    m_deviceToolBar->addAction(addSlitAction);
    m_deviceToolBar->addSeparator();
    m_deviceToolBar->addAction(addPointSourceAction);
    m_deviceToolBar->addSeparator();
    m_deviceToolBar->addAction(removeReflectorAction);
    m_deviceToolBar->addAction(removeLightSourceAction);

    m_zoomToolBar = addToolBar("Zoom Tool Bar");
    m_zoomToolBar->setMovable(true);
    ZoomWidget * zoomWidget = new ZoomWidget(this);
    connect(zoomWidget, SIGNAL(valueChanged(int)), m_system, SLOT(zoom(int)));
    m_zoomToolBar->addAction(QIcon("Icons/ZoomIn.png"), "Zoom In", zoomWidget, SLOT(stepUp()));
    m_zoomToolBar->addWidget(zoomWidget);
    m_zoomToolBar->addAction(QIcon("Icons/ZoomOut.png"), "Zoom Out", zoomWidget, SLOT(stepDown()));
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
