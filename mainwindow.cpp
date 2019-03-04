#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SetStyle();
    if(sqlconnect("elective")){
        qDebug()<<"ok"<<endl;
    }
    else
        qDebug()<<"fail"<<endl;

    connect(this,SIGNAL(sendID1(QString)),&dialog1,SLOT(receiveID1(QString)));
    connect(this,SIGNAL(sendID2(QString)),&dialog2,SLOT(receiveID2(QString)));
    connect(this,SIGNAL(sendID2(QString)),&dialog2,SLOT(init()));
    connect(this,SIGNAL(sendID1(QString)),&dialog1,SLOT(pushButton()));
    connect(this,SIGNAL(sendID3()),&dialog3,SLOT(init()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::sqlconnect(const QString dbname)
{
    QSqlDatabase dataBase=QSqlDatabase::addDatabase("QMYSQL");
    dataBase.setHostName("localhost");
    dataBase.setUserName("root");
    dataBase.setPassword("123456");
    dataBase.setDatabaseName(dbname);
    bool ok=dataBase.open();
    if(ok)
    {
        qDebug()<<"open database success";
        return true;
    }
    else
    {
        qDebug()<<"error open database because"<<dataBase.lastError().text();
        return false;
    }
}

void MainWindow::on_pushButton_clicked()
{
    if(!check())
        return;
    this->hide();
    switch(ui->comboBox->currentIndex()){
    case 0:
        emit sendID1(ui->lineEdit->text());
        dialog1.show();
        dialog1.exec();
        this->show();
        break;
    case 1:
        emit sendID2(ui->lineEdit->text());
        dialog2.show();
        dialog2.exec();
        this->show();
        break;
    case 2:
        emit sendID3();
        dialog3.show();
        dialog3.exec();
        this->show();
        break;
    default:
        break;
    };
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->comboBox->setCurrentIndex(0);
}

bool MainWindow::check()
{
    QSqlQuery query;
    QString id = ui->lineEdit->text();
    QString pass = ui->lineEdit_2->text();
    QString identity = ui->comboBox->currentText();
    QString temp = QString("select count(*) from idpassword where id='%1'").arg(id);
    query.exec(temp);
    query.first();
    bool ok1 = query.value(0).toInt();
    temp = QString("select * from idpassword where id='%1'").arg(id);
    bool ok = query.exec(temp);
    if(ok&&ok1){
        query.first();
        if(pass == query.value(1).toString()){
            if(identity == query.value(2).toString())
                return true;
            else
                QMessageBox::information(this,"提示","请选择对应的身份");
        }
        else
            QMessageBox::information(this,"提示","请输入正确的密码");
    }
    else
        QMessageBox::information(this,"提示","请输入正确的账号");
    return false;

}

void MainWindow::SetStyle()
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
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);

}
