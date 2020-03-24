#include "widget.h"
#include "ui_widget.h"
#include "custombar.h"

#include <QDesktopWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSplitter>
#include <QStatusBar>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
//    this->setWindowState(Qt::WindowMaximized);
    setWindowFlags(Qt::FramelessWindowHint);
//    QDesktopWidget* pw=QApplication::desktop();
//    int desktop_width=pw->screen()->width();
//    int desktop_height=pw->screen()->height();

    int cwidth=1400;
    int cheight=800;
//    setFixedSize(QSize(cwidth,cheight));
    resize(cwidth,cheight);
    customBar* cb=new customBar(this);
    this->installEventFilter(cb);
    this->setWindowTitle("MuCPS");
    QIcon icon("images/i1.png");
    this->setWindowIcon(icon);
//    this->setStyleSheet("QWidget.cb{background:#c3c3c3;border-color:#c3c3c3;}");



//    QPushButton* pb=new QPushButton(this);
//    pb->setFixedHeight(30);
//    pb->setText("this is button mt");


    QStatusBar* sb=new QStatusBar(this);
    sp_main=new QSplitter(Qt::Horizontal,this);
    fr_content=new QFrame(sp_main);
    fr_list=new QFrame(sp_main);

    sp_main->setHandleWidth(2);
    sp_main->setStyleSheet("QSplitter::handle{background:#ffffff");

    fr_content->setStyleSheet("background:#2e2e2e;");

    fr_content->resize(cwidth-200,height());
    fr_content->setMinimumWidth(cwidth-300);
    fr_content->setMaximumWidth(cwidth-50);
    fr_list->setStyleSheet("background:#5c5ef2;");
    fr_list->resize(200,height());
    fr_list->setMaximumWidth(300);
    fr_list->setMinimumWidth(50);



//    sb->showMessage("this is mt");
//   QStatusBar* sb=new QStatusBar(this);
//   sb->setSizeGripEnabled(false);

    QVBoxLayout* vbox=new QVBoxLayout();
    vbox->addWidget(cb,0,Qt::AlignTop);
    vbox->addWidget(sp_main,1);
//    vbox->addStretch(1);
//    vbox->addWidget(pb);
//    vbox->addStretch(1);
    vbox->addWidget(sb,0,Qt::AlignBottom);

    vbox->setSpacing(0);
    vbox->setContentsMargins(0,0,0,0);


    setLayout(vbox);

    btn=new QPushButton(this);
    btn->setFixedSize(50,50);
    btn->setText("OK");
    btn->move(10,100);
    btn->setStyleSheet("QPushButton{background:#cccccc;}");
    connect(btn,SIGNAL(clicked()),this,SLOT(btnOnClick()));

//    cb->move(0,0);

    setMouseTracking(true);

}

Widget::~Widget()
{
    delete ui;
}
/*
void Widget::resizeEvent(QResizeEvent *event)
{
    qDebug()<<"this is resize"<<this->width();
    if(this->width()>1400){
//        sp_main->resize(1920,this->height());
//         fr_content->resize(1720,this->height());
//         fr_list->resize(200,this->height());
         fr_content->resize(1920-200,height());
         fr_content->setMinimumWidth(1920-300);
         fr_content->setMaximumWidth(1920-50);
         fr_list->resize(200,height());
         fr_list->setMaximumWidth(300);
         fr_list->setMinimumWidth(50);

         qDebug()<<"this is resizess";

    }

    if(this->width()<=1400){
        fr_content->setMinimumWidth(1400-300);
        fr_content->setMaximumWidth(1400-50);
        fr_list->setMaximumWidth(300);
        fr_list->setMinimumWidth(50);
        fr_content->resize(1400-200,height());
        fr_list->resize(200,height());
    }



    QWidget::resizeEvent(event);
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){


//        qDebug()<<event->pos().x();
//        qDebug()<<event->x();
        //判断鼠标的范围是不是在右下角10*10的像素中
        const int rb=30;

        if(event->x()>=this->width()-rb and event->x()<this->width() and event->y()>=this->height()-rb and this->y()<this->height()){

            qDebug()<<"##";

            isDragWindow=true;
            start_point=event->globalPos();
            window_rect=this->geometry();
            Qt::CursorShape cursor;
            cursor=Qt::SizeFDiagCursor;
            this->setCursor(cursor);

            this->setGeometry(window_rect.x(),window_rect.y(),1000,400);
        }

    }
//    QWidget::mousePressEvent(event);


}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(isDragWindow){

        QPoint currentPoint=QCursor::pos();
        QPoint distance=currentPoint-start_point;
        QRect currentRect=window_rect;
        qDebug()<<distance;

        currentRect.setBottomRight(window_rect.bottomRight()+distance);
        this->setGeometry(currentRect);
        qDebug()<<"move"<<currentRect<<window_rect<<this;
    }
//    QWidget::mouseMoveEvent(event);
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
      isDragWindow=false;
     QApplication::restoreOverrideCursor();
     Qt::CursorShape cursor;
     cursor=Qt::ArrowCursor;
     this->setCursor(cursor);
//     QWidget::mouseReleaseEvent(event);
}
*/
void Widget::btnOnClick()
{
     QList <int> list;
    if(fr_content->width()<=this->width()-200){
        //最小化

        list.append(this->width()-50);
        list.append(50);
    }
    if(fr_content->width()>this->width()-200){

        list.append(this->width()-200);
        list.append(200);
    }


    sp_main->setSizes(list);
}
