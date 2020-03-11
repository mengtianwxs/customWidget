#ifndef CUSTOMBAR_H
#define CUSTOMBAR_H

#include <QLabel>
#include <QMouseEvent>
#include <QObject>
#include <QPushButton>
#include <QWidget>
#include<QDebug>

class customBar : public QWidget
{
    Q_OBJECT
public:
    explicit customBar(QWidget *parent = nullptr);
private:
    bool isLeftPressed;
    QPoint start_pos;

    QLabel* lal_title;
    QLabel* lal_icon;
    QPushButton* btn_min;
    QPushButton* btn_close;
    QPushButton* btn_max;

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent *event);



    bool eventFilter(QObject* obj,QEvent* event);

protected slots:
    void onClick();

};

#endif // CUSTOMBAR_H
