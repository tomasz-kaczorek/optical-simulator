#include "opticaldevice.h"

#include "label.h"
#include "opticalsystem.h"

OpticalDevice::OpticalDevice(QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
    m_label = new Label("", this);
}

OpticalDevice::~OpticalDevice()
{

}

QString OpticalDevice::name()
{
    return m_label->text();
}

void OpticalDevice::setName(QString name)
{
    m_label->setText(name);
}

OpticalSystem *OpticalDevice::system() const
{
    return static_cast<OpticalSystem *>(scene());
}
