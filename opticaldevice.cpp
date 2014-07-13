#include "opticaldevice.h"

#include "label.h"
#include "normal.h"
#include "opticalsystem.h"
#include "settings.h"

#include <QPainter>

OpticalDevice::OpticalDevice(OpticalSystem * opticalSystem, QGraphicsItem * parent) :
    QGraphicsItem(parent),
    m_opticalSystem(opticalSystem),
    m_label(nullptr),
    m_normal(nullptr)
{
    m_pen = QPen(Settings::primaryColor, Settings::deviceThickness, Qt::SolidLine, Qt::RoundCap);
}

OpticalDevice::~OpticalDevice()
{
}

void OpticalDevice::addLabel()
{
    if(!m_label) m_label = new Label(this);
}

void OpticalDevice::showLabel()
{
    if(m_label) m_label->show();
}

void OpticalDevice::hideLabel()
{
    if(m_label) m_label->hide();
}

void OpticalDevice::addNormal()
{
    if(!m_normal) m_normal = new Normal(this);
}

void OpticalDevice::showNormal()
{
    if(m_normal) m_normal->show();
}

void OpticalDevice::hideNormal()
{
    if(m_normal) m_normal->hide();
}

QString OpticalDevice::name()
{
    return m_label ? m_label->text() : QString();
}

void OpticalDevice::setName(QString name)
{
    if(m_label) m_label->setText(name);
}

QList<Reflector *> const & OpticalDevice::reflectors()
{
    return m_opticalSystem->reflectors();
}

QList<LightSource *> const & OpticalDevice::lightSources()
{
    return m_opticalSystem->lightSources();
}

QRectF OpticalDevice::boundingRect() const
{
    qreal adjustment = m_pen.width();
    return (m_path.boundingRect()).adjusted(-adjustment, -adjustment, adjustment, adjustment);
}

void OpticalDevice::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(m_pen);
    painter->drawPath(m_path);
}
