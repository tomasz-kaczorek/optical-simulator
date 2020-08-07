#include "precisedoublespinbox.h"

#include "settings.h"

#include <float.h>
#include <QLocale>

PreciseDoubleSpinBox::PreciseDoubleSpinBox(QWidget *parent) :
    QDoubleSpinBox(parent),
    m_precision(Settings::decimals)
{
    QDoubleSpinBox::setDecimals(DBL_MAX_10_EXP + DBL_DIG);
}

QString PreciseDoubleSpinBox::textFromValue(double value) const
{
    QString text = QWidget::locale().toString(value, 'f', m_precision);
    text.remove(QRegExp("0+$"));
    text.remove(QRegExp("\\.$"));
    text.remove(QRegExp("\\,$"));
    return text;
}

void PreciseDoubleSpinBox::setDecimals(int prec)
{
    m_precision = prec;
}
