#include "custombar.h"

#include <QHBoxLayout>
#include <QLineEdit>
#include <QSizePolicy>

customBar::customBar(QWidget *parent) : QWidget(parent)
{

//    setWindowFlags(Qt::FramelessWindowHint);
//    setFixedHeight(30);


    lal_icon=new QLabel();
    lal_icon->setFixedSize(30,30);
//    lal_icon->setScaledContents(true);


    lal_title=new QLabel();
    lal_title->setText("this is window title");
    lal_title->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    lal_title->setFixedHeight(30);
    lal_title->setScaledContents(true);
    lal_title->setStyleSheet("color:#ffffff");

    btn_min=new QPushButton();
    btn_max=new QPushButton();
    btn_close=new QPushButton();
    btn_max->setText("+");
    btn_min->setText("-");
    btn_close->setText("x");
    btn_close->setFlat(false);



    btn_min->setStyleSheet(" QPushButton{color:#ffffff;background:transparent;border:none;}QPushButton::hover{background:#00a06e;} ");
    btn_max->setStyleSheet(" QPushButton{color:#ffffff;background:transparent;border:none;}QPushButton::hover{background:#00a06e;} ");
    btn_close->setStyleSheet(" QPushButton{color:#ffffff;background:transparent;border:none;}QPushButton::hover{background:#00a06e;} ");






    btn_min->setFixedSize(27,22);
    btn_max->setFixedSize(27,22);
    btn_close->setFixedSize(27,22);


    QWidget* mainWidget=new QWidget();
    QHBoxLayout* mainLayout=new QHBoxLayout(this);
    mainLayout->addWidget(mainWidget);
    mainWidget->setStyleSheet("QWidget{background:#14af78;}");
    mainWidget->setFixedHeight(30);
    mainLayout->setMargin(0);


//    QFont font("Microsoft YaHei",14,2);
//    lal_title->setFont(font);

    QLineEdit* le=new QLineEdit();
    le->setStyleSheet("QLineEdit{background:#ffffff;}QLineEdit::hover{border:none}");

    QHBoxLayout* hbox=new QHBoxLayout();
    hbox->addWidget(lal_icon);
    hbox->addStretch(1);
    hbox->addWidget(lal_title);
    hbox->addStretch(1);
    hbox->addWidget(le);
    hbox->addWidget(btn_min);
    hbox->addWidget(btn_max);
    hbox->addWidget(btn_close);
    hbox->setSpacing(0);
    hbox->setContentsMargins(0,0,0,0);
//    hbox->SetFixedSize(800,30);
//    setLayout(hbox);
    mainWidget->setLayout(hbox);





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

void customBar::mouseDoubleClickEvent(QMouseEvent *event)
{
        qDebug()<<"doublce";
        QWidget* pw=this->parentWidget();
        if(pw->windowState()==Qt::WindowNoState){
            pw->showMaximized();
        }else if(pw->windowState()==Qt::WindowMaximized){

            pw->showNormal();
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
            if(pw->windowState()==Qt::WindowMaximized){
                pw->setWindowState(Qt::WindowNoState);
                qDebug()<<"normal";
            }else {
               pw->showMaximized();
                qDebug()<<"max";
            }
//           pw->isMaximized()?pw->showNormal():pw->showMaximized();
        }
        if(pb==btn_close){

            pw->close();
        }
    }



}
