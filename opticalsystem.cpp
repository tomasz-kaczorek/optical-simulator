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

OpticalSystem::OpticalSystem(QObject * parent) :
    QGraphicsScene(parent)
{
    m_reflectorsTabs = new OpticalDeviceTabWidget();
    m_lightSourcesTabs = new OpticalDeviceTabWidget();

    setSceneRect(Settings::minX, Settings::minY, Settings::maxX - Settings::minX, Settings::maxY - Settings::minY);
    setBackgroundBrush(QBrush(Settings::backgroundColor));

    m_reflectors.append(new Absorber(Settings::minX - 1.0, Settings::minY - 1.0, Settings::minX - 1.0, Settings::maxY - 1.0, this));
    m_reflectors.append(new Absorber(Settings::minX - 1.0, Settings::maxY + 1.0, Settings::maxX + 1.0, Settings::maxY + 1.0, this));
    m_reflectors.append(new Absorber(Settings::maxX + 1.0, Settings::maxY + 1.0, Settings::maxX + 1.0, Settings::minY - 1.0, this));
    m_reflectors.append(new Absorber(Settings::maxX + 1.0, Settings::minY - 1.0, Settings::minX - 1.0, Settings::minY - 1.0, this));
}

OpticalSystem::~OpticalSystem()
{
    delete m_reflectorsTabs;
    delete m_lightSourcesTabs;
}

void OpticalSystem::addPlaneMirror()
{
    PlaneMirror * planeMirror = new PlaneMirror("Plane Mirror", Settings::minX, Settings::minY, 0.0, Settings::minRadius, this);
    addItem(planeMirror);
    m_reflectors.append(planeMirror);

    PlaneMirrorForm * planeMirrorForm = new PlaneMirrorForm(planeMirror, m_reflectorsTabs);
    m_reflectorsTabs->addTab(planeMirrorForm);
}

void OpticalSystem::addConcaveMirror()
{
    ConcaveMirror * concaveMirror = new ConcaveMirror("Concave Mirror", Settings::minX, Settings::minY, 0.0, Settings::minRadius, Settings::minFocalLength, this);
    addItem(concaveMirror);
    m_reflectors.append(concaveMirror);

    ConcaveMirrorForm * concaveMirrorForm = new ConcaveMirrorForm(concaveMirror, m_reflectorsTabs);
    m_reflectorsTabs->addTab(concaveMirrorForm);
}

void OpticalSystem::addDiffractionGrating()
{
    DiffractionGrating * diffractionGrating = new DiffractionGrating("Diffraction Grating", Settings::minX, Settings::minY, 0.0, Settings::minRadius, 0.0, Settings::minDensity, this);
    addItem(diffractionGrating);
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
        removeItem(reflector);
        delete reflector;
        m_reflectorsTabs->removeCurrentTab();
    }
}

void OpticalSystem::addPointSource()
{
    bool array[5] = {true, true, true, true, true};
    PointSource * pointSource = new PointSource("Point Source", Settings::minX, Settings::minY, 0.0, 0.0, 0, Settings::minWavelength, array, true, this);
    addItem(pointSource);
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
        removeItem(lightSource);
        delete lightSource;
        m_lightSourcesTabs->removeCurrentTab();
    }
}
