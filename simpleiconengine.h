#ifndef SIMPLEICONENGINE_H
#define SIMPLEICONENGINE_H

#include <QIconEngineV2>

class QColor;

class SimpleIconEngine : public QIconEngineV2
{
public:
    SimpleIconEngine(QColor color);
    virtual void paint(QPainter * painter, QRect const & rect, QIcon::Mode mode, QIcon::State state);
private:
    QColor m_color;
};

#endif // SIMPLEICONENGINE_H
