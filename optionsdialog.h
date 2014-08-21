#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>

class QCheckBox;
class QColor;
class QComboBox;
class QIcon;
class QPushButton;
class QToolButton;

class OptionsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit OptionsDialog(QWidget *parent = 0);
    bool normals();
    bool labels();
    int deviceThickness();
    QColor primaryColor();
    QColor secondaryColor();
    QColor backgroundColor();
public slots:
    void normalsChanged(int state);
    void labelsChanged(int state);
    void primaryColorClicked();
    void secondaryColorClicked();
    void backgroundColorClicked();
private:
    QIcon icon(QColor color);
    QCheckBox * m_normalsCheckBox;
    QCheckBox * m_labelsCheckBox;
    QComboBox * m_thicknessComboBox;
    QToolButton * m_primaryColorButton;
    QToolButton * m_secondaryColorButton;
    QToolButton * m_backgroundColorButton;
    QColor m_primaryColor;
    QColor m_secondaryColor;
    QColor m_backgroundColor;
};

#endif // OPTIONSDIALOG_H
