#ifndef OPTICALSYSTEMREADER_H
#define OPTICALSYSTEMREADER_H

#include <QXmlStreamReader>

class OpticalSystem;

class OpticalSystemReader
{
public:
    OpticalSystemReader(OpticalSystem * system);
    void readFile(QString filename);
private:
    void readPlanemirror();
    void readConcaveMirror();
    void readDiffractionGrating();
    void readPointSource();

    QXmlStreamReader m_reader;
    OpticalSystem * m_system;
};

#endif // OPTICALSYSTEMREADER_H
