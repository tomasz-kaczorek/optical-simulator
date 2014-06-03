#ifndef REFLECTORTAB_H
#define REFLECTORTAB_H

#include <QWidget>

class Reflector;
class QGridLayout;
class QLabel;
class QLineEdit;
class QDoubleSpinBox;
class MainWindow;

class ReflectorTab : public QWidget
{
    Q_OBJECT
public:
    explicit ReflectorTab(Reflector * reflector, MainWindow * mainWindow, QWidget * parent = 0);
    virtual ~ReflectorTab();
protected:
    Reflector *m_reflector;
    MainWindow *m_mainWindow;
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
    void newLabel(QWidget *w, const QString &label);
public slots:
    void nameEditingFinished();
    void xValueChanged(double value);
    void yValueChanged(double value);
    void angleValueChanged(double value);
};

#endif // REFLECTORTAB_H
