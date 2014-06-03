#ifndef AIMDIALOG_H
#define AIMDIALOG_H

#include <QDialog>

class DockableTabWidget;
class QVBoxLayout;
class QComboBox;
class QGroupBox;
class QRadioButton;

class AimDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AimDialog(QStringList names, QWidget *parent = 0);
    int getIndex();
    int getChoice();
private:
    QVBoxLayout *m_layout;
    QComboBox *m_reflectorsComboBox;
    QGroupBox *m_groupBox;
    QVBoxLayout *m_groupBoxLayout;
    QRadioButton *m_aimCenterRadioButton;
    QRadioButton *m_aimLeftRadioButton;
    QRadioButton *m_aimRightRadioButton;
    QRadioButton *m_aimBothRadioButton;
    QPushButton *m_okPushButton;
signals:
    
public slots:
    
};

#endif // AIMDIALOG_H
