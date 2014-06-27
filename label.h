#ifndef LABEL_H
#define LABEL_H

#include <QGraphicsSimpleTextItem>

class Label : public QGraphicsSimpleTextItem
{
public:
    Label(QString text, QGraphicsItem *parent = 0);
    void geometryChanged();
    QRectF boundingRect() const;
    void paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget);
private:
    qreal m_adjustment;
};

#endif // LABEL_H
