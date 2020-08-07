#ifndef PRECISEDOUBLESPINBOX_H
#define PRECISEDOUBLESPINBOX_H

#include <QDoubleSpinBox>

class PreciseDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    explicit PreciseDoubleSpinBox(QWidget *parent = 0);
    QString textFromValue(double value) const;

    void setDecimals(int prec);
private:
    int m_precision;
};

#endif // PRECISEDOUBLESPINBOX_H
