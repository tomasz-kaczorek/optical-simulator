#ifndef SIMPLEICONENGINE_H
#define SIMPLEICONENGINE_H

#include <QIconEngine>

class QColor;

class SimpleIconEngine : public QIconEngine
{
public:
    SimpleIconEngine(QColor color);
    virtual void paint(QPainter * painter, QRect const & rect, QIcon::Mode mode, QIcon::State state);
    virtual QIconEngine * clone() const;
private:
    QColor m_color;
};

#endif // SIMPLEICONENGINE_H
