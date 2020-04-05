#include "widget.h"
#include "ui_widget.h"
#include "custombar.h"
#include "customstatusbar.h"

#include <QDesktopWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSizeGrip>
#include <QSplitter>
#include <QStatusBar>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
//    this->setWindowState(Qt::WindowMaximized);
    setWindowFlags(Qt::FramelessWindowHint);
    QDesktopWidget* pw=QApplication::desktop();
    desktop_width=pw->screen()->width();
    desktop_height=pw->screen()->height();

    int cwidth=1400;
    int cheight=800;
//    setFixedSize(QSize(cwidth,cheight));//千万不 能设置成固定尺寸，要不然没法进行比缩放
    resize(cwidth,cheight);
    this->setMinimumSize(QSize(cwidth,cheight));
    customBar* cb=new customBar(this);
    this->installEventFilter(cb);
    this->setWindowTitle("MuCPS");
    QIcon icon("images/i1.png");
    this->setWindowIcon(icon);
//    this->setStyleSheet("QWidget.cb{background:#c3c3c3;border-color:#c3c3c3;}");



//    QPushButton* pb=new QPushButton(this);
//    pb->setFixedHeight(30);
//    pb->setText("this is button mt");


//    QStatusBar* sb=new QStatusBar(this);

//    sb->setSizeGripEnabled(false);

//    sgp=new QSizeGrip(this);
//    sgp->resize(30,30);
//    sgp->move(this->width()-30,this->height()-30);

    sp_main=new QSplitter(Qt::Horizontal,this);
//    sp_main->resize(this->width(),this->height()-100-30);
    fr_content=new QFrame(sp_main);
    fr_list=new QFrame(sp_main);

    sp_main->setHandleWidth(2);
    sp_main->setStyleSheet("QSplitter::handle{background:#ffffff");

    fr_content->setStyleSheet("background:#2e2e2e;");

    fr_content->resize(cwidth-200,height());
//    fr_content->setMinimumWidth(cwidth-300);
    fr_content->setMaximumWidth(cwidth-50);
    fr_list->setStyleSheet("background:#5c5ef2;");
    fr_list->resize(200,height());
    fr_list->setMaximumWidth(300);
//    fr_list->setMinimumWidth(50);



//    sb->showMessage("this is mt");
   QStatusBar* sb=new QStatusBar(this);
//   sb->setSizeGripEnabled(false);
   sb->setAttribute(Qt::WA_TransparentForMouseEvents,true);

    tabWidget=ui->tabWidget;
    tabWidget->resize(this->width(),100);
    tabWidget->setStyleSheet("background-color: red;");

//    customStatusBar* sb=new customStatusBar(this);


    QVBoxLayout* vbox=new QVBoxLayout();
    vbox->addWidget(cb,0,Qt::AlignTop);
    vbox->addWidget(tabWidget,1);
    vbox->addWidget(sp_main,7);
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
    btn->move(10,200);
    btn->setStyleSheet("QPushButton{background:#cccccc;}");
    connect(btn,SIGNAL(clicked()),this,SLOT(btnOnClick()));

   btn_tab=new QPushButton(this);
   btn_tab->setFixedSize(25,20);
   btn_tab->move(this->width()-30,30);
//   btn_tab->setText("zhankai");
   btn_tab->setStyleSheet("QPushButton{color:#ffffff;background:transparent;border:none;}QPushButton::hover{background:#00a06e;} ");

   QPixmap mapup("images/arrowup.png");
   mapup.scaled(25,20);
   iconup=QIcon(mapup);

   QPixmap mapdown("images/arrowdown.png");
   mapdown.scaled(25,20);
   icondown=QIcon(mapdown);
   btn_tab->setIcon(iconup);

   connect(btn_tab,SIGNAL(clicked()),this,SLOT(onzhankai()));

//    cb->move(0,0);

    setMouseTracking(true);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::resizeEvent(QResizeEvent *event)
{
//    qDebug()<<"this is resize"<<this->width();
     btn_tab->move(this->width()-30,30);
    if(this->width()==desktop_width){
//        sp_main->resize(1920,this->height());

//            fr_content->resize(this->width()-200,height());
       fr_content->setMaximumWidth(this->width()-50);
//            fr_list->resize(200,height());
       fr_list->setMaximumWidth(300);

    }

//    if(this->width()<=1400){
//        fr_content->setMinimumWidth(1400-300);
//        fr_content->setMaximumWidth(1400-50);
//        fr_list->setMaximumWidth(300);
//        fr_list->setMinimumWidth(50);
//        fr_content->resize(1400-200,height());
//        fr_list->resize(200,height());
//    }



//    QWidget::resizeEvent(event);
}



void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){


//        qDebug()<<event->pos().x();
//        qDebug()<<event->x();
        //判断鼠标的范围是不是在右下角10*10的像素中
        const int rb=50;

        if(event->x()>=this->width()-rb and event->x()<this->width() and event->y()>=this->height()-rb and this->y()<this->height()){

            qDebug()<<"##";

            isDragWindow=true;
            start_point=event->globalPos();
            window_rect=this->geometry();
            Qt::CursorShape cursor;
            cursor=Qt::SizeFDiagCursor;
            this->setCursor(cursor);

//            this->setGeometry(window_rect.x(),window_rect.y(),1000,400);
        }

    }
//    QWidget::mousePressEvent(event);


}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    qDebug()<<"cc";

    const int rb=50;

    if(event->x()>=this->width()-rb and event->x()<this->width() and event->y()>=this->height()-rb and this->y()<this->height()){
        Qt::CursorShape cursor;
        cursor=Qt::SizeFDiagCursor;
        this->setCursor(cursor);
    }
    if(isDragWindow){

        QPoint currentPoint=QCursor::pos();
        QPoint distance=currentPoint-start_point;
        QRect currentRect=window_rect;
//        qDebug()<<distance;

        currentRect.setBottomRight(window_rect.bottomRight()+distance);
        this->setGeometry(currentRect);

//        sgp->move(this->width()-30,this->height()-30);
        qDebug()<<"move"<<currentRect<<window_rect<<this;


        if(this->width()>1400 and this->width()<desktop_width){
             btn_tab->move(this->width()-30,30);
//            fr_content->resize(this->width()-200,height());
            fr_content->setMaximumWidth(this->width()-50);
//            fr_list->resize(200,height());
            fr_list->setMaximumWidth(300);


        }
    }


    QWidget::mouseMoveEvent(event);
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

void Widget::onzhankai()
{
//    qDebug()<<"clcik";
    if(tabWidget->height()>20){
        tabWidget->setFixedHeight(20);
        btn_tab->setIcon(icondown);
        qDebug()<<"this si 1";
    }
    else{
        tabWidget->setFixedHeight(100);
        qDebug()<<"this is 2";
        btn_tab->setIcon(iconup);
    }
}
