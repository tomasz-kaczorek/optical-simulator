#ifndef ZOOMWIDGET_H
#define ZOOMWIDGET_H

#include <QWidget>

class QSpinBox;
class QPushButton;

class ZoomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ZoomWidget(QWidget *parent = 0);
signals:
    void valueChanged(int);
public slots:
    void menu(QAction * action);
    void stepUp();
    void stepDown();
private:
    QSpinBox * m_zoomSpinBox;
    QPushButton * m_zoomButton;
    int m_values[14];
};

#endif // ZOOMWIDGET_H
