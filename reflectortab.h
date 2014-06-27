#ifndef REFLECTORTAB_H
#define REFLECTORTAB_H

#include <QWidget>

class QDoubleSpinBox;
class QGridLayout;
class QLabel;
class QLineEdit;
class QPushButton;

class ReflectorTab : public QWidget
{
    Q_OBJECT
public:
    explicit ReflectorTab(QWidget * parent = 0);
    virtual ~ReflectorTab();
protected:
    QGridLayout *m_layout;
    QLabel *m_nameLabel;
    QLineEdit *m_nameLineEdit;
    QLabel *m_xLabel;
    QDoubleSpinBox *m_xSpinBox;
    QLabel *m_yLabel;
    QDoubleSpinBox *m_ySpinBox;
    QLabel *m_angleLabel;
    QDoubleSpinBox *m_angleSpinBox;
signals:
    void newName(const QString &label);
public slots:
    virtual void apply(bool) = 0;
    virtual void cancel(bool) = 0;
    virtual void remove(bool checked) = 0;
};

#endif // REFLECTORTAB_H
