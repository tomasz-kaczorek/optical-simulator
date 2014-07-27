#include "label.h"
#include "settings.h"
#include <QPainter>
#include <qmath.h>

Label::Label(QGraphicsItem * parent) :
    QGraphicsSimpleTextItem(parent)
{
    setFlag(QGraphicsItem::ItemIgnoresTransformations);
    setFlag(QGraphicsItem::ItemStacksBehindParent);
    setBrush(QBrush(Settings::secondaryColor));
    setFont(QFont("Arial", 8));
    setRotation(0.0);
}

void Label::setRotation(qreal angle)
{
    prepareGeometryChange();
    //recalculates cosinusoidal adjustment to the distance between label and parent item
    m_adjustment = -qFabs(qSin(angle * M_PI / 180.0));
}

QRectF Label::boundingRect() const
{
    QRectF boundingRect = QGraphicsSimpleTextItem::boundingRect();
    //centers bounding rectangle around point (0.0, 0.0)
    boundingRect.moveCenter(QPointF(0.0, 0.0));
    return boundingRect;
}

void Label::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    //ensure regular distance between label and parent item
    setY(-m_adjustment * QGraphicsSimpleTextItem::boundingRect().width() / 2.0 + 10.0);
    //begin painting in the center of label
    painter->translate(-boundingRect().width() / 2.0, -boundingRect().height() / 2.0);
    QGraphicsSimpleTextItem::paint(painter, option, widget);
}
