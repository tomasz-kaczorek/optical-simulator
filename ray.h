#ifndef RAY_H
#define RAY_H

#include "lightsource.h"

#include <QGraphicsLineItem>

class Reflector;

//custom QGraphicsItem offers better control over paint function and faster access to line attributes than QGraphicsLineItem
class Ray : public QGraphicsLineItem
{
public:
    Ray(LightSource *lightSource, qreal x1, qreal y1, qreal x2, qreal y2, unsigned int recursionDepth = 0, int order = 0, QGraphicsItem *parent = 0);
    Ray(LightSource *lightSource, qreal x1, qreal y1, qreal angle, unsigned int recursionDepth = 0, int order = 0, QGraphicsItem *parent = 0);

    inline void adjust(qreal adjustment);
    inline qreal wavelength() const;
    void setWavelength(qreal wavelength);
    inline bool visibleOrder(int order) const;
    void setVisibleOrder(int order, bool visible = true);

    void plot();
    void plot(Reflector *reflector);

    void reflect(qreal x, qreal y, int order = 0);
    void reflect(qreal angle, int order = 0);
private:
    unsigned int m_recursionDepth;
    LightSource *m_lightSource;
    Reflector *m_reflector;
    Ray *m_next[5];
    static unsigned int counter;
};

void Ray::adjust(qreal adjustment)
{
    QLineF newLine = line();
    newLine.setLength(newLine.length() * adjustment);
    setLine(newLine);
}

qreal Ray::wavelength() const
{
    return m_lightSource->wavelength();
}

bool Ray::visibleOrder(int order) const
{
    return m_lightSource->visibleOrder(order);
}

#endif // RAY_H
