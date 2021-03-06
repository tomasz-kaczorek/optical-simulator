#ifndef OPTICALSYSTEMWRITER_H
#define OPTICALSYSTEMWRITER_H

#include <QXmlStreamWriter>

class ConcaveMirror;
class DiffractionGrating;
class OpticalSystem;
class PlaneMirror;
class PointSource;
class Slit;

class OpticalSystemWriter
{
public:
    OpticalSystemWriter(OpticalSystem * system);
    void writeFile(QString filename);
private:
    void writePlaneMirror(PlaneMirror * item);
    void writeConcaveMirror(ConcaveMirror * item);
    void writeDiffractionGrating(DiffractionGrating * item);
    void writeSlit(Slit * item);
    void writePointSource(PointSource * item);

    QXmlStreamWriter m_writer;
    OpticalSystem * m_system;
};

#endif // OPTICALSYSTEMWRITER_H
