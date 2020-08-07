#include "simpleiconengine.h"

#include <QPainter>

SimpleIconEngine::SimpleIconEngine(QColor color) :
    m_color(color)
{
}

void SimpleIconEngine::paint(QPainter * painter, const QRect & rect, QIcon::Mode, QIcon::State)
{
    painter->drawRect(rect.adjusted(0, 0, -1, -1));
    painter->fillRect(rect.adjusted(1, 1, -1, -1), QBrush(m_color));
}

QIconEngine *SimpleIconEngine::clone() const
{
    return new SimpleIconEngine(m_color);
}
