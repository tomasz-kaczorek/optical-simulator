#ifndef LIGHTSOURCETAB_H
#define LIGHTSOURCETAB_H

#include <QWidget>

class MainWindow;
class LightSource;
class QGridLayout;
class QLabel;
class QLineEdit;
class QDoubleSpinBox;
class QSpinBox;
class QGroupBox;
class QCheckBox;
class QPushButton;

class LightSourceTab : public QWidget
{
    Q_OBJECT
public:
    explicit LightSourceTab(LightSource *lightSource, MainWindow *mainWindow, QWidget *parent = 0);
private:
    MainWindow *m_mainWindow;
    LightSource *m_lightSource;
    QGridLayout *m_layout;
    QLabel *m_nameLabel;
    QLineEdit *m_nameLineEdit;
    QLabel *m_xLabel;
    QDoubleSpinBox *m_xSpinBox;
    QLabel *m_yLabel;
    QDoubleSpinBox *m_ySpinBox;
    QLabel *m_beginAngleLabel;
    QDoubleSpinBox *m_beginAngleSpinBox;
    QLabel *m_endAngleLabel;
    QDoubleSpinBox *m_endAngleSpinBox;
    QLabel *m_quantityLabel;
    QSpinBox *m_quantitySpinBox;
    QLabel *m_wavelengthLabel;
    QDoubleSpinBox *m_wavelengthSpinBox;
    QGroupBox *m_visibleOrdersGroupBox;
    QGridLayout *m_visibleOrdersLayout;
    QCheckBox *m_secondNegativeOrderCheckBox;
    QCheckBox *m_firstNegativeOrderCheckBox;
    QCheckBox *m_zeroOrderCheckBox;
    QCheckBox *m_firstPositiveOrderCheckBox;
    QCheckBox *m_secondPositiveOrderCheckBox;
    QPushButton *m_aimPushButton;
    QCheckBox *m_activeCheckBox;
signals:
    void newLabel(QWidget *w, const QString &label);
public slots:
    void nameEditingFinished();
    void xValueChanged(double value);
    void yValueChanged(double value);
    void beginAngleValueChanged(double value);
    void endAngleValueChanged(double value);
    void quantityValueChanged(int value);
    void wavelengthValueChanged(double value);
    void visibleOrdersStateChanged();
    void activateStateChanged();
    void aim();
};

#endif // LIGHTSOURCETAB_H
