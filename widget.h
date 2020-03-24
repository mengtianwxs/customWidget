#ifndef WIDGET_H
#define WIDGET_H

#include <QFrame>
#include <QPushButton>
#include <QSplitter>
#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    QPushButton* btn;
    QSplitter* sp_main;
    QFrame* fr_content;
    QFrame* fr_list;

    bool isDragWindow=false;
    QPoint start_point;
    QRect window_rect;

//    void resizeEvent(QResizeEvent *event);//实现右边控制调整
//    void mousePressEvent(QMouseEvent* event);//实现窗口缩放功能
//    void mouseMoveEvent(QMouseEvent* event);//实现窗口缩放功能
//    void mouseReleaseEvent(QMouseEvent* event);//实现窗口缩放功能

public slots:
    void btnOnClick();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
