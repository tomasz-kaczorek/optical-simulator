#ifndef NORMAL_H
#define NORMAL_H

#include <QGraphicsItem>

#include <QBrush>
#include <QPen>

class Normal : public QGraphicsItem
{
public:
    Normal(QGraphicsItem * parent = 0);
    void setGeometry();
    void setBrush(QBrush brush);
protected:
    QRectF boundingRect() const;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
private:
    QPen m_pen;
    QPainterPath m_path;
};

#endif // NORMAL_H
