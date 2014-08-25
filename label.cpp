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
    qreal cos = qCos(angle * M_PI / 180.0);
    m_horizontalAdjustment = (-1.0 - cos) * QGraphicsSimpleTextItem::boundingRect().width() / 2.0 - 10.0 * cos;
    qreal sin = qSin(angle * M_PI / 180.0);
    m_verticalAdjustment = (-1.0 - sin) * QGraphicsSimpleTextItem::boundingRect().height() / 2.0 - 10.0 * sin;
}

QRectF Label::boundingRect() const
{
    QRectF boundingRect = QGraphicsSimpleTextItem::boundingRect();
    return boundingRect.translated(m_horizontalAdjustment, m_verticalAdjustment);
}

void Label::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    painter->setRenderHint(QPainter::TextAntialiasing);
    painter->translate(m_horizontalAdjustment, m_verticalAdjustment);
    QGraphicsSimpleTextItem::paint(painter, option, widget);
}
