#include "opticalsystemwriter.h"

#include "concavemirror.h"
#include "diffractiongrating.h"
#include "opticalsystem.h"
#include "planemirror.h"
#include "pointsource.h"
#include "settings.h"

#include <QFile>

OpticalSystemWriter::OpticalSystemWriter(OpticalSystem * system) :
    m_system(system)
{
}

void OpticalSystemWriter::writeFile(QString filename)
{
    QFile file(filename);
    file.open(QIODevice::WriteOnly);
    m_writer.setDevice(&file);
    m_writer.writeStartDocument();
    m_writer.writeStartElement("OpticalSystem");
    m_writer.writeStartElement("SceneRectangle");
    m_writer.writeTextElement("minX", QString::number(Settings::minX));
    m_writer.writeTextElement("maxX", QString::number(Settings::maxX));
    m_writer.writeTextElement("minY", QString::number(Settings::minY));
    m_writer.writeTextElement("maxY", QString::number(Settings::maxY));
    m_writer.writeEndElement();
    m_writer.writeStartElement("Reflectors");
    foreach(Reflector * reflector, m_system->reflectors())
    {
        if(reflector->type() == OpticalDevice::PlaneMirror)
        {
            writePlaneMirror(static_cast<PlaneMirror *>(reflector));
        }
        else if(reflector->type() == OpticalDevice::ConcaveMirror)
        {
            writeConcaveMirror(static_cast<ConcaveMirror *>(reflector));
        }
        else if(reflector->type() == OpticalDevice::DiffractionGrating)
        {
            writeDiffractionGrating(static_cast<DiffractionGrating *>(reflector));
        }
    }
    m_writer.writeEndElement();
    m_writer.writeStartElement("LightSources");
    foreach(LightSource * lightSource, m_system->lightSources())
    {
        if(lightSource->type() == OpticalDevice::PointSource)
        {
            writePointSource(static_cast<PointSource *>(lightSource));
        }
    }
    m_writer.writeEndElement();
    m_writer.writeEndDocument();
    file.close();
}

void OpticalSystemWriter::writePlaneMirror(PlaneMirror * item)
{
    m_writer.writeStartElement("PlaneMirror");
    m_writer.writeTextElement("Name", item->name());
    m_writer.writeTextElement("X", QString::number(item->x()));
    m_writer.writeTextElement("Y", QString::number(item->y()));
    m_writer.writeTextElement("Angle", QString::number(item->rotation()));
    m_writer.writeTextElement("Radius", QString::number(item->radius()));
    m_writer.writeEndElement();
}

void OpticalSystemWriter::writeConcaveMirror(ConcaveMirror * item)
{
    m_writer.writeStartElement("ConcaveMirror");
    m_writer.writeTextElement("Name", item->name());
    m_writer.writeTextElement("X", QString::number(item->x()));
    m_writer.writeTextElement("Y", QString::number(item->y()));
    m_writer.writeTextElement("Angle", QString::number(item->rotation()));
    m_writer.writeTextElement("Radius", QString::number(item->radius()));
    m_writer.writeTextElement("FocalLength", QString::number(item->focalLength()));
    m_writer.writeEndElement();
}

void OpticalSystemWriter::writeDiffractionGrating(DiffractionGrating * item)
{
    m_writer.writeStartElement("DiffractionGrating");
    m_writer.writeTextElement("Name", item->name());
    m_writer.writeTextElement("X", QString::number(item->x()));
    m_writer.writeTextElement("Y", QString::number(item->y()));
    m_writer.writeTextElement("Angle", QString::number(item->rotation()));
    m_writer.writeTextElement("Radius", QString::number(item->radius()));
    m_writer.writeTextElement("BlazeAngle", QString::number(item->blazeAngle()));
    m_writer.writeTextElement("Density", QString::number(item->density()));
    m_writer.writeEndElement();
}

void OpticalSystemWriter::writePointSource(PointSource * item)
{
    m_writer.writeStartElement("PointSource");
    m_writer.writeTextElement("Name", item->name());
    m_writer.writeTextElement("X", QString::number(item->x()));
    m_writer.writeTextElement("Y", QString::number(item->y()));
    m_writer.writeTextElement("BeginAngle", QString::number(item->beginAngle()));
    m_writer.writeTextElement("EndAngle", QString::number(item->endAngle()));
    m_writer.writeTextElement("Quantity", QString::number(item->quantity()));
    m_writer.writeTextElement("Wavelength", QString::number(item->wavelength()));
    m_writer.writeStartElement("VisibleOrders");
    m_writer.writeTextElement("SecondNegative", item->order(-2) ? "Yes" : "No");
    m_writer.writeTextElement("FirstNegative", item->order(-1) ? "Yes" : "No");
    m_writer.writeTextElement("Zero", item->order(0) ? "Yes" : "No");
    m_writer.writeTextElement("FirstPositive", item->order(1) ? "Yes" : "No");
    m_writer.writeTextElement("SecondPositive", item->order(2) ? "Yes" : "No");
    m_writer.writeEndElement();
    m_writer.writeTextElement("Active", item->active() ? "Yes" : "No");
    m_writer.writeEndElement();
}
