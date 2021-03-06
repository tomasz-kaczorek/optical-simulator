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
    setZValue(1.0);
}

OpticalDevice::~OpticalDevice()
{
}

OpticalSystem *OpticalDevice::system()
{
    return m_opticalSystem;
}

void OpticalDevice::addLabel()
{
    if(!m_label) m_label = new Label(this);
    if(!Settings::labels) m_label->hide();
}

void OpticalDevice::showLabel()
{
    if(m_label) m_label->show();
}

void OpticalDevice::hideLabel()
{
    if(m_label) m_label->hide();
}

void OpticalDevice::newLabelPen()
{
    if(m_label) m_label->setBrush(QBrush(Settings::secondaryColor));
}

void OpticalDevice::addNormal()
{
    if(!m_normal) m_normal = new Normal(this);
    if(!Settings::normals) m_normal->hide();
}

void OpticalDevice::showNormal()
{
    if(m_normal) m_normal->show();
}

void OpticalDevice::hideNormal()
{
    if(m_normal) m_normal->hide();
}

void OpticalDevice::newNormalPen()
{
    if(m_normal) m_normal->setBrush(QBrush(Settings::secondaryColor));
}

void OpticalDevice::newPen()
{
    prepareGeometryChange();
    m_pen.setColor(Settings::primaryColor);
    m_pen.setWidthF(Settings::deviceThickness);
}

QString OpticalDevice::name() const
{
    return m_label ? m_label->text() : QString();
}

void OpticalDevice::setName(QString name)
{
    if(m_label) m_label->setName(name);
}

QList<Reflector *> const & OpticalDevice::reflectors()
{
    return m_opticalSystem->reflectors();
}

QList<LightSource *> const & OpticalDevice::lightSources()
{
    return m_opticalSystem->lightSources();
}

void OpticalDevice::setRotation(qreal angle)
{
    if(m_label) m_label->setRotation(angle);
    if(m_normal) m_normal->setRotation(angle);
    QGraphicsItem::setRotation(angle);
}

QRectF OpticalDevice::boundingRect() const
{
    qreal adjustment = m_pen.width() / 2.0;
    return (m_path.boundingRect()).adjusted(-adjustment, -adjustment, adjustment, adjustment);
}

void OpticalDevice::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(m_pen);
    painter->drawPath(m_path);
}
