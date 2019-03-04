#include "dialog3_5.h"
#include "ui_dialog3_5.h"

Dialog3_5::Dialog3_5(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog3_5)
{
    ui->setupUi(this);
    SetStyle();
}

Dialog3_5::~Dialog3_5()
{
    delete ui;
}

void Dialog3_5::on_pushButton_clicked()  //开放选课
{
    QSqlQuery query;
    QString temp;
    temp = QString("update open set YN='1' where whether='choosecourse'");
    bool ok = query.exec(temp);
    if(ok){
        refresh();
        QMessageBox::information(this,"提示","开放选课成功");}
    else
        QMessageBox::information(this,"提示","开放选课失败");
}

void Dialog3_5::init()
{
    refresh();
}

void Dialog3_5::refresh()
{
    QSqlQuery query;
    QString temp;
    temp = QString("select * from open where whether='choosecourse'");
    query.exec(temp);query.first();
    bool ok = query.value(1).toInt();
    if(ok)
        ui->label_3->setText("可以选课");
    else
        ui->label_3->setText("禁止选课");
    temp = QString("select * from open where whether='entergrade'");
    query.exec(temp);query.first();
    ok = query.value(1).toInt();
    if(ok)
        ui->label_4->setText("可以录入成绩");
    else
        ui->label_4->setText("禁止录入成绩");
}

void Dialog3_5::on_pushButton_2_clicked()
{
    QSqlQuery query;
    QString temp;
    temp = QString("update open set YN='0' where whether='choosecourse'");
    bool ok = query.exec(temp);
    if(ok){
        refresh();
        QMessageBox::information(this,"提示","关闭选课成功");}
    else
        QMessageBox::information(this,"提示","关闭选课失败");
}

void Dialog3_5::on_pushButton_3_clicked()
{
    QSqlQuery query;
    QString temp;
    temp = QString("update open set YN='1' where whether='entergrade'");
    bool ok = query.exec(temp);
    if(ok){
        refresh();
        QMessageBox::information(this,"提示","开放录入成绩成功");}
    else
        QMessageBox::information(this,"提示","开放录入成绩失败");
}

void Dialog3_5::on_pushButton_4_clicked()
{
    QSqlQuery query;
    QString temp;
    temp = QString("update open set YN='0' where whether='entergrade'");
    bool ok = query.exec(temp);
    if(ok){
        refresh();
        QMessageBox::information(this,"提示","关闭录入成绩成功");}
    else
        QMessageBox::information(this,"提示","关闭录入成绩失败");
}

void Dialog3_5::SetStyle()
{
    QString pushstyle = QString("QPushButton{background-color: #63B8FF;border-style: outset;border-width: 2px;border-radius: 5px;border-color: #87CEFF;\
                                font: bold 24px;min-width:2em;color:white;font-family:华文新魏;padding: 5px;}\
                                QPushButton:hover{background-color: #48D1CC;}QPushButton:pressed {background-color: #1E90FF;border-style: inset;}\
                                QPushButton:!enabled{background-color: rgb(100, 100, 100);border-style: inset;}");
    ui->pushButton->setStyleSheet(pushstyle);
    ui->pushButton_2->setStyleSheet(pushstyle);
    ui->pushButton_3->setStyleSheet(pushstyle);
    ui->pushButton_4->setStyleSheet(pushstyle);
}
