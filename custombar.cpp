#include "custombar.h"

#include <QHBoxLayout>
#include <QSizePolicy>

customBar::customBar(QWidget *parent) : QWidget(parent)
{
    setFixedHeight(30);
    setWindowFlags(Qt::FramelessWindowHint);


    lal_icon=new QLabel(this);
    lal_icon->setFixedSize(30,30);
//    lal_icon->setScaledContents(true);


    lal_title=new QLabel(this);
    lal_title->setText("this is window title");
//    lal_title->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    lal_title->setFixedHeight(30);
    lal_title->setScaledContents(true);

    btn_min=new QPushButton(this);
    btn_max=new QPushButton(this);
    btn_close=new QPushButton(this);



    btn_min->setFixedSize(27,22);
    btn_max->setFixedSize(27,22);
    btn_close->setFixedSize(27,22);




//    QFont font("Microsoft YaHei",14,2);
//    lal_title->setFont(font);
    QHBoxLayout* hbox=new QHBoxLayout();
    hbox->addWidget(lal_icon);
    hbox->addStretch(1);
    hbox->addWidget(lal_title);
    hbox->addStretch(1);
    hbox->addWidget(btn_min);
    hbox->addWidget(btn_max);
    hbox->addWidget(btn_close);
    hbox->setSpacing(0);
    hbox->setContentsMargins(0,0,0,0);
    setLayout(hbox);



     this->setStyleSheet("QHBoxLayout,QWidget,QPushButton,QLabel{background:transparent;background-color:#c2c2c2;}");

    connect(btn_min,SIGNAL(clicked()),this,SLOT(onClick()));
    connect(btn_max,SIGNAL(clicked()),this,SLOT(onClick()));
    connect(btn_close,SIGNAL(clicked()),this,SLOT(onClick()));

}

void customBar::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        isLeftPressed=true;
        start_pos=event->globalPos();
    }
}

void customBar::mouseMoveEvent(QMouseEvent *event)
{
    if(isLeftPressed){
        parentWidget()->move(parentWidget()->geometry().topLeft()+event->globalPos()-start_pos);
        start_pos=event->globalPos();
    }
}

void customBar::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        isLeftPressed=false;
    }
}

bool customBar::eventFilter(QObject *obj, QEvent *event)
{
    QWidget* pw=qobject_cast<QWidget*>(obj);


    switch (event->type()) {
    case QEvent::WindowTitleChange:
        if(pw){

            lal_title->setText(pw->windowTitle());
            return true;
        }

        break;

    case QEvent::WindowIconChange:
        if(pw){
            QIcon icon=pw->windowIcon();
            lal_icon->setPixmap(icon.pixmap(lal_icon->size()));
            return true;


        }

    }

    return QWidget::eventFilter(obj,event);



}

void customBar::onClick()
{
    QWidget* pw=this->parentWidget();
    QPushButton* pb=qobject_cast<QPushButton*>(sender());

    if(pw->isTopLevel()){

        if(pb==btn_min){

            pw->showMinimized();
        }
        if(pb==btn_max){
           pw->isMaximized()?pw->showNormal():pw->showMaximized();
        }
        if(pb==btn_close){

            pw->close();
        }
    }



}
