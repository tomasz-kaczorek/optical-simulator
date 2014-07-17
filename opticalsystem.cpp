#include "opticalsystem.h"

#include "absorber.h"
#include "concavemirror.h"
#include "concavemirrorform.h"
#include "diffractiongrating.h"
#include "diffractiongratingform.h"
#include "pointsource.h"
#include "pointsourceform.h"
#include "opticaldevicetabwidget.h"
#include "planemirror.h"
#include "planemirrorform.h"
#include "reflector.h"
#include "settings.h"

#include <QDockWidget>
#include <QFile>
#include <QFileDialog>
#include <QGraphicsView>
#include <QMainWindow>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

OpticalSystem::OpticalSystem(QMainWindow * parent) :
    QGraphicsView(parent)
{
    m_scene = new QGraphicsScene(this);
    m_scene->setSceneRect(Settings::minX, Settings::minY, Settings::maxX - Settings::minX, Settings::maxY - Settings::minY);
    m_scene->setBackgroundBrush(QBrush(Settings::backgroundColor));
    setScene(m_scene);
    ensureVisible(Settings::minX, Settings::minY, 0.0, 0.0);

    QDockWidget * reflectorDockWidget = new QDockWidget(tr("Reflectors"), this);
    m_reflectorsTabs = new OpticalDeviceTabWidget(reflectorDockWidget);
    reflectorDockWidget->setWidget(m_reflectorsTabs);

    QDockWidget * lightSourceDockWidget = new QDockWidget(tr("Light Sources"), this);
    m_lightSourcesTabs = new OpticalDeviceTabWidget(lightSourceDockWidget);
    lightSourceDockWidget->setWidget(m_lightSourcesTabs);

    parent->setCentralWidget(this);
    parent->addDockWidget(Qt::BottomDockWidgetArea, reflectorDockWidget);
    parent->addDockWidget(Qt::BottomDockWidgetArea, lightSourceDockWidget);

    m_reflectors.append(new Absorber(Settings::minX - 1.0, Settings::minY - 1.0, Settings::minX - 1.0, Settings::maxY - 1.0, this));
    m_reflectors.append(new Absorber(Settings::minX - 1.0, Settings::maxY + 1.0, Settings::maxX + 1.0, Settings::maxY + 1.0, this));
    m_reflectors.append(new Absorber(Settings::maxX + 1.0, Settings::maxY + 1.0, Settings::maxX + 1.0, Settings::minY - 1.0, this));
    m_reflectors.append(new Absorber(Settings::maxX + 1.0, Settings::minY - 1.0, Settings::minX - 1.0, Settings::minY - 1.0, this));
}

OpticalSystem::~OpticalSystem()
{
    delete m_reflectors.takeFirst();
    delete m_reflectors.takeFirst();
    delete m_reflectors.takeFirst();
    delete m_reflectors.takeFirst();
}

void OpticalSystem::open()
{

}

#include <QDebug>

void OpticalSystem::save()
{
    QFile file(QFileDialog::getSaveFileName(this, "Save System", QString(), "XML files (*.xml)"));
    file.open(QIODevice::WriteOnly);
    QXmlStreamWriter writer(&file);
    writer.writeStartDocument("1.0");
    writer.writeStartElement("OpticalScene");
    writer.writeAttribute("minX", QString::number(Settings::minX));
    writer.writeAttribute("maxX", QString::number(Settings::maxX));
    writer.writeAttribute("minY", QString::number(Settings::minY));
    writer.writeAttribute("maxY", QString::number(Settings::maxY));
    writer.writeStartElement("Reflectors");
    foreach(Reflector * reflector, m_reflectors) reflector->save(&writer);
    writer.writeEndElement();
    writer.writeStartElement("LightSources");
    foreach(LightSource * lightSource, m_lightSources) lightSource->save(&writer);
    writer.writeEndElement();
    writer.writeEndDocument();
    file.close();
}

void OpticalSystem::addPlaneMirror()
{
    PlaneMirror * planeMirror = new PlaneMirror("Plane Mirror", Settings::minX, Settings::minY, 0.0, Settings::minRadius, this);
    m_scene->addItem(planeMirror);
    m_reflectors.append(planeMirror);

    PlaneMirrorForm * planeMirrorForm = new PlaneMirrorForm(planeMirror, m_reflectorsTabs);
    m_reflectorsTabs->addTab(planeMirrorForm);
}

void OpticalSystem::addConcaveMirror()
{
    ConcaveMirror * concaveMirror = new ConcaveMirror("Concave Mirror", Settings::minX, Settings::minY, 0.0, Settings::minRadius, Settings::minFocalLength, this);
    m_scene->addItem(concaveMirror);
    m_reflectors.append(concaveMirror);

    ConcaveMirrorForm * concaveMirrorForm = new ConcaveMirrorForm(concaveMirror, m_reflectorsTabs);
    m_reflectorsTabs->addTab(concaveMirrorForm);
}

void OpticalSystem::addDiffractionGrating()
{
    DiffractionGrating * diffractionGrating = new DiffractionGrating("Diffraction Grating", Settings::minX, Settings::minY, 0.0, Settings::minRadius, 0.0, Settings::minDensity, this);
    m_scene->addItem(diffractionGrating);
    m_reflectors.append(diffractionGrating);

    DiffractionGratingForm * diffractionGratingForm = new DiffractionGratingForm(diffractionGrating, m_reflectorsTabs);
    m_reflectorsTabs->addTab(diffractionGratingForm);
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
    PointSource * pointSource = new PointSource("Point Source", Settings::minX, Settings::minY, 0.0, 0.0, 0, Settings::minWavelength, array, true, this);
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
