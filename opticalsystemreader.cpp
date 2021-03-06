#include "opticalsystemreader.h"

#include "opticalsystem.h"
#include "orders.h"
#include "settings.h"

#include <QFile>

OpticalSystemReader::OpticalSystemReader(OpticalSystem * system) :
    m_system(system)
{
}

void OpticalSystemReader::readFile(QString filename)
{
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    m_reader.setDevice(&file);
    if(m_reader.readNextStartElement() && m_reader.name() == "OpticalSystem")
    {
        if(m_reader.readNextStartElement() && m_reader.name() == "SceneRectangle")
        {
            if(m_reader.readNextStartElement() && m_reader.name() == "minX") Settings::minX = m_reader.readElementText().toDouble();
            if(m_reader.readNextStartElement() && m_reader.name() == "maxX") Settings::maxX = m_reader.readElementText().toDouble();
            if(m_reader.readNextStartElement() && m_reader.name() == "minY") Settings::minY = m_reader.readElementText().toDouble();
            if(m_reader.readNextStartElement() && m_reader.name() == "maxY") Settings::maxY = m_reader.readElementText().toDouble();
            if(m_reader.readNext() == QXmlStreamReader::EndElement && m_reader.name() == "SceneRectangle") m_system->newScene();
        }
        if(m_reader.readNextStartElement() && m_reader.name() == "Reflectors")
        {
            while(m_reader.readNextStartElement())
            {
                if(m_reader.name() == "PlaneMirror") readPlanemirror();
                else if(m_reader.name() == "ConcaveMirror") readConcaveMirror();
                else if(m_reader.name() == "DiffractionGrating") readDiffractionGrating();
                else if(m_reader.name() == "Slit") readSlit();
                else m_reader.skipCurrentElement();
            }
        }
        if(m_reader.readNextStartElement() && m_reader.name() == "LightSources")
        {
            while(m_reader.readNextStartElement())
            {
                if(m_reader.name() == "PointSource") readPointSource();
                else m_reader.skipCurrentElement();
            }
        }
    }
    file.close();
}

void OpticalSystemReader::readPlanemirror()
{
    QString name;
    qreal x;
    qreal y;
    qreal angle;
    qreal radius;
    if(m_reader.readNextStartElement() && m_reader.name() == "Name") name = m_reader.readElementText();
    if(m_reader.readNextStartElement() && m_reader.name() == "X") x = m_reader.readElementText().toDouble();
    if(m_reader.readNextStartElement() && m_reader.name() == "Y") y = m_reader.readElementText().toDouble();
    if(m_reader.readNextStartElement() && m_reader.name() == "Angle") angle = m_reader.readElementText().toDouble();
    if(m_reader.readNextStartElement() && m_reader.name() == "Radius") radius = m_reader.readElementText().toDouble();
    if(m_reader.readNext() == QXmlStreamReader::EndElement && m_reader.name() == "PlaneMirror") m_system->addPlaneMirror(name, x, y, angle, radius);
}

void OpticalSystemReader::readConcaveMirror()
{
    QString name;
    qreal x;
    qreal y;
    qreal angle;
    qreal radius;
    qreal focalLength;
    if(m_reader.readNextStartElement() && m_reader.name() == "Name") name = m_reader.readElementText();
    if(m_reader.readNextStartElement() && m_reader.name() == "X") x = m_reader.readElementText().toDouble();
    if(m_reader.readNextStartElement() && m_reader.name() == "Y") y = m_reader.readElementText().toDouble();
    if(m_reader.readNextStartElement() && m_reader.name() == "Angle") angle = m_reader.readElementText().toDouble();
    if(m_reader.readNextStartElement() && m_reader.name() == "Radius") radius = m_reader.readElementText().toDouble();
    if(m_reader.readNextStartElement() && m_reader.name() == "FocalLength") focalLength = m_reader.readElementText().toDouble();
    if(m_reader.readNext() == QXmlStreamReader::EndElement && m_reader.name() == "ConcaveMirror") m_system->addConcaveMirror(name, x, y, angle, radius, focalLength);
}

void OpticalSystemReader::readDiffractionGrating()
{
    QString name;
    qreal x;
    qreal y;
    qreal angle;
    qreal radius;
    qreal blazeAngle;
    qreal density;
    if(m_reader.readNextStartElement() && m_reader.name() == "Name") name = m_reader.readElementText();
    if(m_reader.readNextStartElement() && m_reader.name() == "X") x = m_reader.readElementText().toDouble();
    if(m_reader.readNextStartElement() && m_reader.name() == "Y") y = m_reader.readElementText().toDouble();
    if(m_reader.readNextStartElement() && m_reader.name() == "Angle") angle = m_reader.readElementText().toDouble();
    if(m_reader.readNextStartElement() && m_reader.name() == "Radius") radius = m_reader.readElementText().toDouble();
    if(m_reader.readNextStartElement() && m_reader.name() == "BlazeAngle") blazeAngle = m_reader.readElementText().toDouble();
    if(m_reader.readNextStartElement() && m_reader.name() == "Density") density = m_reader.readElementText().toDouble();
    if(m_reader.readNext() == QXmlStreamReader::EndElement && m_reader.name() == "DiffractionGrating") m_system->addDiffractionGrating(name, x, y, angle, radius, blazeAngle, density);
}

void OpticalSystemReader::readSlit()
{
    QString name;
    qreal x;
    qreal y;
    qreal angle;
    qreal radius;
    qreal slitRadius;
    if(m_reader.readNextStartElement() && m_reader.name() == "Name") name = m_reader.readElementText();
    if(m_reader.readNextStartElement() && m_reader.name() == "X") x = m_reader.readElementText().toDouble();
    if(m_reader.readNextStartElement() && m_reader.name() == "Y") y = m_reader.readElementText().toDouble();
    if(m_reader.readNextStartElement() && m_reader.name() == "Angle") angle = m_reader.readElementText().toDouble();
    if(m_reader.readNextStartElement() && m_reader.name() == "Radius") radius = m_reader.readElementText().toDouble();
    if(m_reader.readNextStartElement() && m_reader.name() == "SlitRadius") slitRadius = m_reader.readElementText().toDouble();
    if(m_reader.readNext() == QXmlStreamReader::EndElement && m_reader.name() == "Slit") m_system->addSlit(name, x, y, angle, radius, slitRadius);
}

void OpticalSystemReader::readPointSource()
{
    QString name;
    qreal x;
    qreal y;
    qreal beginAngle;
    qreal endAngle;
    int quantity;
    qreal wavelength;
    Orders orders;
    bool active;
    if(m_reader.readNextStartElement() && m_reader.name() == "Name") name = m_reader.readElementText();
    if(m_reader.readNextStartElement() && m_reader.name() == "X") x = m_reader.readElementText().toDouble();
    if(m_reader.readNextStartElement() && m_reader.name() == "Y") y = m_reader.readElementText().toDouble();
    if(m_reader.readNextStartElement() && m_reader.name() == "BeginAngle") beginAngle = m_reader.readElementText().toDouble();
    if(m_reader.readNextStartElement() && m_reader.name() == "EndAngle") endAngle = m_reader.readElementText().toDouble();
    if(m_reader.readNextStartElement() && m_reader.name() == "Quantity") quantity = m_reader.readElementText().toInt();
    if(m_reader.readNextStartElement() && m_reader.name() == "Wavelength") wavelength = m_reader.readElementText().toDouble();
    if(m_reader.readNextStartElement() && m_reader.name() == "VisibleOrders")
    {
        if(m_reader.readNextStartElement() && m_reader.name() == "SecondNegative") orders.set(Orders::SecondNegative, m_reader.readElementText() == "Yes");
        if(m_reader.readNextStartElement() && m_reader.name() == "FirstNegative") orders.set(Orders::FirstNegative, m_reader.readElementText() == "Yes");
        if(m_reader.readNextStartElement() && m_reader.name() == "Zero") orders.set(Orders::Zero, m_reader.readElementText() == "Yes");
        if(m_reader.readNextStartElement() && m_reader.name() == "FirstPositive") orders.set(Orders::FirstPositive, m_reader.readElementText() == "Yes");
        if(m_reader.readNextStartElement() && m_reader.name() == "SecondPositive") orders.set(Orders::SecondPositive, m_reader.readElementText() == "Yes");
        if(m_reader.readNextStartElement() && m_reader.name() == "Max") orders.set(Orders::Max, m_reader.readElementText() == "Yes");
        m_reader.readNext();
    }
    if(m_reader.readNextStartElement() && m_reader.name() == "Active") active = (m_reader.readElementText() == "Yes");
    if(m_reader.readNext() == QXmlStreamReader::EndElement && m_reader.name() == "PointSource") m_system->addPointSource(name, x, y, beginAngle, endAngle, quantity, wavelength, orders, active);
}
