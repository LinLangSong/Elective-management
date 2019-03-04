#include "dialog1_1.h"
#include "ui_dialog1_1.h"

Dialog1_1::Dialog1_1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog1_1)
{
    ui->setupUi(this);
    SetStyle();
}

Dialog1_1::~Dialog1_1()
{
    delete ui;
}

void Dialog1_1::on_pushButton_clicked()
{
    QSqlQuery query;
    QString temp,id,oldpassword,newpassword;
    id = ui->label->text();
    temp = QString("select * from idpassword where id='%1'").arg(id);
    query.exec(temp);
    query.first();
    oldpassword = query.value(1).toString();
    if(ui->lineEdit->text() != ui->lineEdit_2->text())
        QMessageBox::information(this,"提示","请输入相同的密码");
    else if(ui->lineEdit->text() == oldpassword)
        QMessageBox::information(this,"提示","请输入不一样的密码");
    else{
        newpassword = ui->lineEdit->text();
        temp = QString("update idpassword set password='%1' where id='%2'").arg(newpassword).arg(id);
        query.exec(temp);
        query.first();
        QMessageBox::information(this,"提示","修改成功");
        this->close();
    }
}

void Dialog1_1::receiveID1_1(QString ID)
{
    id = ID;
    ui->label->setText(ID);
}

void Dialog1_1::on_pushButton_2_clicked()
{
    this->close();
}

void Dialog1_1::SetStyle()
{
    QString pushstyle = QString("QPushButton{background-color: #63B8FF;border-style: outset;border-width: 2px;border-radius: 5px;border-color: #87CEFF;\
                                font: bold 24px;min-width:2em;color:white;font-family:华文新魏;padding: 5px;}\
                                QPushButton:hover{background-color: #48D1CC;}QPushButton:pressed {background-color: #1E90FF;border-style: inset;}\
                                QPushButton:!enabled{background-color: rgb(100, 100, 100);border-style: inset;}");
    QString linestyle = QString("QLineEdit{border-width:1px;border-radius:4px;font-size:16px;color:black;border:2px solid gray;}"
                                "QLineEdit:hover{background:#FFFACD;border-width:1px;border-radius:4px;font-size:12px;color:black;border:2px solid black;}"
                                "QLineEdit:focus{background:#FFF68F;border-width:1px;border-radius:4px;font-size:12px;color:black;border:2px solid black;}");
    ui->pushButton->setStyleSheet(pushstyle);
    ui->pushButton_2->setStyleSheet(pushstyle);
    ui->lineEdit->setStyleSheet(linestyle);
    ui->lineEdit_2->setStyleSheet(linestyle);
    ui->lineEdit->setEchoMode(QLineEdit::Password);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
}
