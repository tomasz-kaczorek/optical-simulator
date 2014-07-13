#include "normal.h"

#include "settings.h"

#include <QPainter>

Normal::Normal(QGraphicsItem * parent) :
    QGraphicsItem(parent)
{
    m_pen = QPen(Settings::secondaryColor, 0.0, Qt::SolidLine, Qt::RoundCap);
    m_path.lineTo(0.0, -10.0);
    m_path.lineTo(-2.0, -5.0);
    m_path.moveTo(0.0, -10.0);
    m_path.lineTo(2.0, -5.0);
}

QRectF Normal::boundingRect() const
{
    return m_path.boundingRect();
}

void Normal::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(m_pen);
    painter->drawPath(m_path);
}
