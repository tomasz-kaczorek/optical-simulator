#ifndef SIZEDIALOG_H
#define SIZEDIALOG_H

#include <QDialog>

class QDoubleSpinBox;

class SizeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SizeDialog(QWidget *parent = 0);
    qreal minX();
    qreal maxX();
    qreal minY();
    qreal maxY();
private:
    QDoubleSpinBox * m_minXSpinBox;
    QDoubleSpinBox * m_maxXSpinBox;
    QDoubleSpinBox * m_minYSpinBox;
    QDoubleSpinBox * m_maxYSpinBox;
};

#endif // SIZEDIALOG_H
