#ifndef RAY_H
#define RAY_H

#include <QGraphicsLineItem>

#include "lightsource.h"
#include "orders.h"

class Reflector;

class Ray : public QGraphicsLineItem
{
public:
    Ray(LightSource * lightSource, qreal x1, qreal y1, qreal x2, qreal y2, unsigned int recursionDepth = 0, Qt::PenStyle style = Qt::SolidLine, QGraphicsItem * parent = 0);
    Ray(LightSource * lightSource, qreal x1, qreal y1, qreal angle, unsigned int recursionDepth = 0, Qt::PenStyle style = Qt::SolidLine, QGraphicsItem * parent = 0);
    Ray(qreal x, qreal y, qreal angle, qreal wavelength, Orders const & orders, QPen const & pen, QList<Reflector *> const & reflectors, QGraphicsItem * parent = 0);
    Ray(unsigned int recursionDepth, qreal x1, qreal y1, qreal x2, qreal y2, qreal wavelength, Orders const & orders, QPen const & pen, QList<Reflector *> const & reflectors, QGraphicsItem * parent = 0);
    ~Ray();

    qreal wavelength() const;
    bool order(Orders::Order order) const;

    void plot();
    void replot(Orders orders);
    void replot(qreal wavelength, QColor color, Orders orders);
    void replot(Reflector * reflector);

    void append(qreal x, qreal y);
    void append(qreal x, qreal y, Orders::Order order);
private:
    void adjust(qreal adjustment);
    void remove(int i);
    void removeAll();

    unsigned int m_recursionDepth;
    qreal m_wavelength;
    Orders m_orders;
    Ray * m_rays[6];
    Reflector * m_reflector;
    QList<Reflector *> const & m_reflectors;
protected: //QGraphicsLineItem
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
};

#endif // RAY_H
