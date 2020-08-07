#include "normal.h"

#include "settings.h"

#include <QPainter>

Normal::Normal(QGraphicsItem * parent) :
    QGraphicsItem(parent)
{
    setFlag(QGraphicsItem::ItemIgnoresTransformations);
    m_pen = QPen(Settings::secondaryColor, 0.0, Qt::SolidLine, Qt::RoundCap);
    m_path.moveTo(1.0, 0.0);
    m_path.lineTo(10.0, 0.0);
    m_path.lineTo(5.0, -2.0);
    m_path.moveTo(10.0, 0.0);
    m_path.lineTo(5.0, 2.0);
}

void Normal::setBrush(QBrush brush)
{
    prepareGeometryChange();
    m_pen.setBrush(brush);
}

QRectF Normal::boundingRect() const
{
    return m_path.boundingRect();
}

void Normal::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(m_pen);
    painter->drawPath(m_path);
}
