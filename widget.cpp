#include "widget.h"
#include "ui_widget.h"
#include "custombar.h"

#include <QDesktopWidget>
#include <QHBoxLayout>
#include <QPushButton>
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

    setFixedSize(QSize(800,600));
    customBar* cb=new customBar(this);
    this->installEventFilter(cb);
    this->setWindowTitle("mt pptest");
    QIcon icon("images/i1.png");
    this->setWindowIcon(icon);
//    this->setStyleSheet("QWidget.cb{background:#c3c3c3;border-color:#c3c3c3;}");



    QPushButton* pb=new QPushButton(this);
    pb->setFixedHeight(30);
    pb->setText("this is button mt");


    QStatusBar* sb=new QStatusBar(this);

    QVBoxLayout* vbox=new QVBoxLayout();
    vbox->addWidget(cb);
    vbox->addStretch(1);
    vbox->addWidget(pb);
    vbox->addStretch(1);
    vbox->addWidget(sb);

    vbox->setSpacing(0);
    vbox->setContentsMargins(0,0,0,0);


    setLayout(vbox);

//    cb->move(0,0);

}

Widget::~Widget()
{
    delete ui;
}
