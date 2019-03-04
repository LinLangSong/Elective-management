#include "dialog3.h"
#include "ui_dialog3.h"

Dialog3::Dialog3(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog3)
{
    ui->setupUi(this);
    connect(this,SIGNAL(teacher()),&dialog3_1,SLOT(init()));
    connect(this,SIGNAL(student()),&dialog3_2,SLOT(init()));
    connect(this,SIGNAL(course()),&dialog3_3,SLOT(init()));
    connect(this,SIGNAL(major()),&dialog3_4,SLOT(init()));
    connect(this,SIGNAL(oc()),&dialog3_5,SLOT(init()));
}

Dialog3::~Dialog3()
{
    delete ui;
}

void Dialog3::on_pushButton_clicked()
{
    emit teacher();
    dialog3_1.exec();
}

void Dialog3::init()
{
    QString pushstyle = QString("QPushButton{background-color: #63B8FF;border-style: outset;border-width: 2px;border-radius: 5px;border-color: #87CEFF;\
                                font: bold 24px;min-width:2em;color:white;font-family:华文新魏;padding: 5px;}\
                                QPushButton:hover{background-color: #48D1CC;}QPushButton:pressed {background-color: #1E90FF;border-style: inset;}\
                                QPushButton:!enabled{background-color: rgb(100, 100, 100);border-style: inset;}");
    ui->pushButton->setStyleSheet(pushstyle);
    ui->pushButton_2->setStyleSheet(pushstyle);
    ui->pushButton_3->setStyleSheet(pushstyle);
    ui->pushButton_4->setStyleSheet(pushstyle);
    ui->pushButton_5->setStyleSheet(pushstyle);


}

void Dialog3::on_pushButton_2_clicked()
{
    emit student();
    dialog3_2.exec();
}

void Dialog3::on_pushButton_3_clicked()
{
    emit course();
    dialog3_3.exec();
}

void Dialog3::on_pushButton_4_clicked()
{
    emit major();
    dialog3_4.exec();
}

void Dialog3::on_pushButton_5_clicked()
{
    emit oc();
    dialog3_5.exec();
}
