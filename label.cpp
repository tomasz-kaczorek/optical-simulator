#include "label.h"
#include <QPainter>
#include <qmath.h>

Label::Label(QString text, QGraphicsItem *parent) :
    QGraphicsSimpleTextItem(text, parent)
{
    setFlag(QGraphicsItem::ItemIgnoresTransformations);
    setBrush(QBrush(Qt::darkGray));
    setFont(QFont("Arial", 8));
}

void Label::geometryChanged()
{
    //recalculates cosinusoidal adjustment to the distance between label and parent item
    m_adjustment = -qFabs(qCos(parentItem()->rotation() * M_PI / 180.0));
}

QRectF Label::boundingRect() const
{
    QRectF boundingRect = QGraphicsSimpleTextItem::boundingRect();
    //centers bounding rectangle around point (0.0, 0.0)
    boundingRect.moveCenter(QPointF(0.0, 0.0));
    return boundingRect;
}

void Label::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //ensure regular distance between label and parent item
    setX(m_adjustment * QGraphicsSimpleTextItem::boundingRect().width() / 2.0 - 10);
    //begin painting in the center of label
    painter->translate(-boundingRect().width() / 2.0, -boundingRect().height() / 2);
    QGraphicsSimpleTextItem::paint(painter, option, widget);
}
