#ifndef RAY_H
#define RAY_H

#include <QGraphicsItem>

//custom QGraphicsItem offers better control over paint function and faster access to line attributes than QGraphicsLineItem
class Ray : public QGraphicsItem
{
public:
    Ray(qreal x1, qreal y1, qreal x2, qreal y2, QColor color, Qt::PenStyle style);
    Ray *addNext(qreal x, qreal y, int order = 0);
    inline qreal x1() const;
    inline qreal y1() const;
    inline qreal x2() const;
    inline qreal y2() const;
    inline qreal dx() const;
    inline qreal dy() const;
    inline void setAngle(qreal angle);
    inline void adjust(qreal adjustment);
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QLineF m_line;
    QColor m_color;
    Qt::PenStyle m_penStyle;
    Ray *m_next[5];
};

qreal Ray::x1() const
{
    return m_line.x1();
}

qreal Ray::y1() const
{
    return m_line.y1();
}

qreal Ray::x2() const
{
    return m_line.x2();
}

qreal Ray::y2() const
{
    return m_line.y2();
}

qreal Ray::dx() const
{
    return m_line.x2() - m_line.x1();
}

qreal Ray::dy() const
{
    return m_line.y2() - m_line.y1();
}

void Ray::setAngle(qreal angle)
{
    prepareGeometryChange();
    m_line.setAngle(angle);
}

void Ray::adjust(qreal adjustment)
{
    prepareGeometryChange();
    m_line.setLength(m_line.length() * adjustment);
}

#endif // RAY_H
