#include "opticalsystem.h"

#include "absorber.h"
#include "concavemirror.h"
#include "concavemirrorform.h"
#include "diffractiongrating.h"
#include "diffractiongratingform.h"
#include "opticaldevicetabwidget.h"
#include "opticalsystemreader.h"
#include "opticalsystemwriter.h"
#include "optionsdialog.h"
#include "planemirror.h"
#include "planemirrorform.h"
#include "pointsource.h"
#include "pointsourceform.h"
#include "reflector.h"
#include "settings.h"
#include "sizedialog.h"
#include "slit.h"
#include "slitform.h"

#include <QDockWidget>
#include <QFile>
#include <QFileDialog>
#include <QGraphicsView>
#include <QList>
#include <QMainWindow>
#include <QWheelEvent>

OpticalSystem::OpticalSystem(QMainWindow * parent) :
    QGraphicsView(parent),
    m_filename("")
{
    m_scene = new QGraphicsScene(this);
    m_scene->setSceneRect(Settings::minX, Settings::minY, Settings::maxX - Settings::minX, Settings::maxY - Settings::minY);
    m_scene->setBackgroundBrush(QBrush(Settings::backgroundColor));
    setScene(m_scene);
    ensureVisible(Settings::minX, Settings::minY, 0.0, 0.0);

    m_reflectorsTabs = new OpticalDeviceTabWidget(this);
    m_lightSourcesTabs = new OpticalDeviceTabWidget(this);

    newScene();
}

OpticalSystem::~OpticalSystem()
{
    qDeleteAll(m_lightSources);
    qDeleteAll(m_reflectors);
}

void OpticalSystem::newScene()
{
    if(m_reflectors.count() > 0)
    {
        qDeleteAll(m_lightSources);
        m_lightSources.clear();
        m_lightSourcesTabs->removeAllTabs();
        qDeleteAll(m_reflectors);
        m_reflectors.clear();
        m_reflectorsTabs->removeAllTabs();
    }
    m_reflectors.append(new Absorber(Settings::minX - 1.0, Settings::minY - 1.0, Settings::minX - 1.0, Settings::maxY - 1.0, this));
    m_reflectors.append(new Absorber(Settings::minX - 1.0, Settings::maxY + 1.0, Settings::maxX + 1.0, Settings::maxY + 1.0, this));
    m_reflectors.append(new Absorber(Settings::maxX + 1.0, Settings::maxY + 1.0, Settings::maxX + 1.0, Settings::minY - 1.0, this));
    m_reflectors.append(new Absorber(Settings::maxX + 1.0, Settings::minY - 1.0, Settings::minX - 1.0, Settings::minY - 1.0, this));
    m_scene->setSceneRect(Settings::minX, Settings::minY, Settings::maxX - Settings::minX, Settings::maxY - Settings::minY);
}

void OpticalSystem::addPlaneMirror()
{
    addPlaneMirror("Plane Mirror", Settings::minX, Settings::minY, 0.0, Settings::minRadius);
}

void OpticalSystem::addPlaneMirror(QString name, qreal x, qreal y, qreal angle, qreal radius)
{
    PlaneMirror * planeMirror = new PlaneMirror(name, x, y, angle, radius, this);
    m_scene->addItem(planeMirror);
    m_reflectors.append(planeMirror);

    PlaneMirrorForm * planeMirrorForm = new PlaneMirrorForm(planeMirror, m_reflectorsTabs);
    m_reflectorsTabs->addTab(planeMirrorForm);
}

void OpticalSystem::addConcaveMirror()
{
    addConcaveMirror("Concave Mirror", Settings::minX, Settings::minY, 0.0, Settings::minRadius, Settings::minFocalLength);
}

void OpticalSystem::addConcaveMirror(QString name, qreal x, qreal y, qreal angle, qreal radius, qreal focalLength)
{
    ConcaveMirror * concaveMirror = new ConcaveMirror(name, x, y, angle, radius, focalLength, this);
    m_scene->addItem(concaveMirror);
    m_reflectors.append(concaveMirror);

    ConcaveMirrorForm * concaveMirrorForm = new ConcaveMirrorForm(concaveMirror, m_reflectorsTabs);
    m_reflectorsTabs->addTab(concaveMirrorForm);
}

void OpticalSystem::addDiffractionGrating()
{
    addDiffractionGrating("Diffraction Grating", Settings::minX, Settings::minY, 0.0, Settings::minRadius, 0.0, Settings::minDensity);
}

void OpticalSystem::addDiffractionGrating(QString name, qreal x, qreal y, qreal angle, qreal radius, qreal blazeAngle, qreal density)
{
    DiffractionGrating * diffractionGrating = new DiffractionGrating(name, x, y, angle, radius, blazeAngle, density, this);
    m_scene->addItem(diffractionGrating);
    m_reflectors.append(diffractionGrating);

    DiffractionGratingForm * diffractionGratingForm = new DiffractionGratingForm(diffractionGrating, m_reflectorsTabs);
    m_reflectorsTabs->addTab(diffractionGratingForm);
}

void OpticalSystem::addSlit()
{
    addSlit("Slit", Settings::minX, Settings::minY, 0.0, Settings::minRadius, 0.0);
}

void OpticalSystem::addSlit(QString name, qreal x, qreal y, qreal angle, qreal radius, qreal slitRadius)
{
    Slit * slit = new Slit(name, x, y, angle, radius, slitRadius, this);
    m_scene->addItem(slit);
    m_reflectors.append(slit);

    SlitForm * slitForm = new SlitForm(slit, m_reflectorsTabs);
    m_reflectorsTabs->addTab(slitForm);
}

void OpticalSystem::removeReflector()
{
    int index = m_reflectorsTabs->currentIndex();
    if(index >= 0)
    {
        Reflector * reflector = m_reflectors.takeAt(index + 4);
        m_scene->removeItem(reflector);
        delete reflector;
        m_reflectorsTabs->removeCurrentTab();
    }
}

void OpticalSystem::addPointSource()
{
    bool array[5] = {true, true, true, true, true};
    addPointSource("Point Source", Settings::minX, Settings::minY, 0.0, 0.0, 0, Settings::minWavelength, array, true);
}

void OpticalSystem::addPointSource(QString name, qreal x, qreal y, qreal beginAngle, qreal endAngle, int quantity, qreal wavelength, bool orders[], bool active)
{
    PointSource * pointSource = new PointSource(name, x, y, beginAngle, endAngle, quantity, wavelength, orders, active, this);
    m_scene->addItem(pointSource);
    m_lightSources.append(pointSource);

    PointSourceForm *pointSourceForm = new PointSourceForm(pointSource, m_lightSourcesTabs);
    m_lightSourcesTabs->addTab(pointSourceForm);
}

void OpticalSystem::removeLightSource()
{
    int index = m_lightSourcesTabs->currentIndex();
    if(index >= 0)
    {
        LightSource * lightSource = m_lightSources.takeAt(index);
        m_scene->removeItem(lightSource);
        delete lightSource;
        m_lightSourcesTabs->removeCurrentTab();
    }
}

QGraphicsScene * OpticalSystem::scene()
{
    return m_scene;
}

OpticalDeviceTabWidget * OpticalSystem::reflectorsTabs()
{
    return m_reflectorsTabs;
}

OpticalDeviceTabWidget * OpticalSystem::lightSourcesTabs()
{
    return m_lightSourcesTabs;
}

QList<Reflector *> const & OpticalSystem::reflectors()
{
    return m_reflectors;
}

QList<LightSource *> const & OpticalSystem::lightSources()
{
    return m_lightSources;
}

void OpticalSystem::newSystem()
{
    SizeDialog sizeDialog(this);
    if(sizeDialog.exec() == QDialog::Accepted)
    {
        Settings::minX = sizeDialog.minX();
        Settings::maxX = sizeDialog.maxX();
        Settings::minY = sizeDialog.minY();
        Settings::maxY = sizeDialog.maxY();
        newScene();
    }
}

void OpticalSystem::openSystem()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open System", QString(), "XML files (*.xml)");
    if(filename.isEmpty()) return;
    m_filename = filename;
    OpticalSystemReader reader(this);
    reader.readFile(m_filename);
}

void OpticalSystem::saveSystem()
{
    if(m_filename.isEmpty())
    {
        saveSystemAs();
    }
    else
    {
        OpticalSystemWriter writer(this);
        writer.writeFile(m_filename);
    }
}

void OpticalSystem::saveSystemAs()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save System", QString(), "XML files (*.xml)");
    if(filename.isEmpty()) return;
    m_filename = filename;
    OpticalSystemWriter writer(this);
    writer.writeFile(m_filename);
}

void OpticalSystem::zoom(int scale)
{
    setTransform(transform().fromScale(scale / 100.0, scale / 100.0));
}

void OpticalSystem::options()
{
    OptionsDialog optionsDialog(this);
    if(optionsDialog.exec() == QDialog::Accepted)
    {
        const bool newPen = Settings::primaryColor != optionsDialog.primaryColor() || Settings::deviceThickness != optionsDialog.deviceThickness();
        const bool newChildPen = Settings::secondaryColor != optionsDialog.secondaryColor();
        const bool showLabels = !Settings::labels && optionsDialog.labels();
        const bool hideLabels = Settings::labels && !optionsDialog.labels();
        const bool showNormals = !Settings::normals && optionsDialog.normals();
        const bool hideNormals = Settings::normals && !optionsDialog.normals();

        Settings::normals = optionsDialog.normals();
        Settings::labels = optionsDialog.labels();
        Settings::deviceThickness = optionsDialog.deviceThickness();
        Settings::primaryColor = optionsDialog.primaryColor();
        Settings::secondaryColor = optionsDialog.secondaryColor();
        if(Settings::backgroundColor != optionsDialog.backgroundColor()) m_scene->setBackgroundBrush(QBrush(Settings::backgroundColor = optionsDialog.backgroundColor()));
        foreach(Reflector * reflector, m_reflectors)
        {
            if(newPen) reflector->newPen();
            if(newChildPen)
            {
                reflector->newLabelPen();
                reflector->newNormalPen();
            }
            if(showLabels) reflector->showLabel();
            if(hideLabels) reflector->hideLabel();
            if(showNormals) reflector->showNormal();
            if(hideNormals) reflector->hideNormal();
        }
        foreach(LightSource * lightSource, m_lightSources)
        {
            if(newPen) lightSource->newPen();
            if(newChildPen)
            {
                lightSource->newLabelPen();
                lightSource->newNormalPen();
            }
            if(showLabels) lightSource->showLabel();
            if(hideLabels) lightSource->hideLabel();
            if(showNormals) lightSource->showNormal();
            if(hideNormals) lightSource->hideNormal();
        }
    }
}
