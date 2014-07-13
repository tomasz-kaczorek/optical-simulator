#ifndef RAY_H
#define RAY_H

#include "lightsource.h"

#include <QGraphicsLineItem>

class Reflector;

class Ray : public QGraphicsLineItem
{
public:
    Ray(LightSource * lightSource, qreal x1, qreal y1, qreal x2, qreal y2, unsigned int recursionDepth = 0, Qt::PenStyle style = Qt::SolidLine, QGraphicsItem * parent = 0);
    Ray(LightSource * lightSource, qreal x1, qreal y1, qreal angle, unsigned int recursionDepth = 0, Qt::PenStyle style = Qt::SolidLine, QGraphicsItem * parent = 0);
    ~Ray();

    inline qreal wavelength();
    inline bool order(int order);

    void plot();
    void replot(bool orders[5]);
    void replot(Reflector * reflector);

    void append(qreal x, qreal y);
    void append(qreal x, qreal y, int order);
private:
    inline void adjust(qreal adjustment);
    inline void remove(int order);

    unsigned int m_recursionDepth;
    LightSource * m_lightSource;
    Ray * m_rays[5];
    Reflector * m_reflector;
};

qreal Ray::wavelength()
{
    return m_lightSource->wavelength();
}

bool Ray::order(int order)
{
    //returns true if the specified diffraction order is desired but not present
    //returns false otherwise
    return order >= -2 && order <= 2 && !m_rays[order + 2] && m_lightSource->order(order);
}

void Ray::adjust(qreal adjustment)
{
    QLineF newLine = line();
    newLine.setLength(newLine.length() * adjustment);
    setLine(newLine);
}

void Ray::remove(int order)
{
    delete m_rays[order + 2];
    m_rays[order + 2] = nullptr;
}

#endif // RAY_H
