#include "ray.h"
#include "settings.h"
#include <QPainter>
#include <QGraphicsScene>

Ray::Ray(qreal x1, qreal y1, qreal x2, qreal y2, QColor color, Qt::PenStyle style) :
    m_line(x1, y1, x2, y2),
    m_color(color),
    m_penStyle(style),
    m_next{nullptr, nullptr, nullptr, nullptr, nullptr}
{
}

Ray *Ray::addNext(qreal x, qreal y, int order)
{
    if(order == 0)
    {
        m_next[2] = new Ray(x2(), y2(), x, y, m_color, Qt::SolidLine);
    }
    else if(order == -1 || order == 1)
    {
        m_next[order + 2] = new Ray(x2(), y2(), x, y, m_color, Qt::DashLine);
    }
    else m_next[order + 2] = new Ray(x2(), y2(), x, y, m_color, Qt::DotLine);
    scene()->addItem(m_next[order + 2]);
    return m_next[order + 2];
}

QRectF Ray::boundingRect() const
{
    qreal x;
    qreal y;
    qreal dx;
    qreal dy;
    if(x1() < x2())
    {
        x = x1();
        dx = x2() - x1();
    }
    else
    {
        x = x2();
        dx = x1() - x2();
    }
    if(y1() < y2())
    {
        y = y1();
        dy = y2() - y1();
    }
    else
    {
        y = y2();
        dy = y1() - y2();
    }
    return QRectF(x - Settings::rayPenWidth / 2, y - Settings::rayPenWidth / 2, dx + Settings::rayPenWidth, dy + Settings::rayPenWidth);
}

void Ray::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(QPen(m_color, Settings::rayPenWidth, m_penStyle));
    painter->drawLine(m_line);
}
