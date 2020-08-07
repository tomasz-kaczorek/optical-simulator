#ifndef AIMDIALOG_H
#define AIMDIALOG_H

#include <QDialog>

class OpticalDevice;
class Reflector;

class QComboBox;
class QDoubleSpinBox;

class AimDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AimDialog(OpticalDevice * opticalDevice, QWidget * parent = 0);
    bool hasBeginPoint();
    QPointF beginPoint();
    bool hasEndPoint();
    QPointF endPoint();
private:
    QList<Reflector *> const & m_reflectors;
    QComboBox * m_beginAnglePointComboBox;
    QComboBox * m_beginAngleReflectorComboBox;
    QComboBox * m_endAnglePointComboBox;
    QComboBox * m_endAngleReflectorComboBox;
};

#endif // AIMDIALOG_H
