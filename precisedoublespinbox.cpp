#include "precisedoublespinbox.h"

#include "settings.h"

#include <float.h>
#include <QLocale>

PreciseDoubleSpinBox::PreciseDoubleSpinBox(QWidget *parent) :
    QDoubleSpinBox(parent)
{
    QDoubleSpinBox::setDecimals(DBL_MAX_10_EXP + DBL_DIG);
}

QString PreciseDoubleSpinBox::textFromValue(double value) const
{
    return QWidget::locale().toString(value, 'f', m_precision);
}

void PreciseDoubleSpinBox::setDecimals(int prec)
{
    m_precision = prec;
}
