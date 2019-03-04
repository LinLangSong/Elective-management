#include "dialog3_2.h"
#include "ui_dialog3_2.h"

Dialog3_2::Dialog3_2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog3_2)
{
    ui->setupUi(this);
    SetStyle();

}

Dialog3_2::~Dialog3_2()
{
    delete ui;
}

void Dialog3_2::on_pushButton_clicked()   //删除学生
{
    bool focus = ui->tableWidget->isItemSelected(ui->tableWidget->currentItem()); //判断是否选中一行
    if(focus){
        int row = ui->tableWidget->currentItem()->row();
        QSqlQuery query;
        QString sqltemp;
        sqltemp = QString("select Sid from student where Sclass='%1'").arg(ui->comboBox_2->currentText());
        query.exec(sqltemp);
        query.first();
        for(int i=1;i<=row;i++){
            query.next();
        }
        QString Sid = query.value(0).toString();

        sqltemp = QString("delete from cs where Sid='%1'").arg(Sid);
        bool ok1 = query.exec(sqltemp);    //删除选课表里学生信息
        sqltemp = QString("delete from student where Sid='%1'").arg(Sid);
        bool ok2 = query.exec(sqltemp);    //删除教师所教课程
        sqltemp = QString("delete from idpassword where id='%1'").arg(Sid);
        bool ok3 = query.exec(sqltemp);  //删除登录信息
        if(ok1&&ok2&&ok3){
            QMessageBox::information(this,"提示","删除成功");
        }
        else
            QMessageBox::information(this,"提示","删除");
        refresh(ui->comboBox_2->currentText());

    }
    else
        QMessageBox::information(this,"提示","请选择一位学生");
}

void Dialog3_2::init()
{
    int i=0;
    ui->comboBox->clear();
    QSqlQuery query;
    QString temp;
    temp = QString("select * from major");
    query.exec(temp);
    while(query.next()){
        ui->comboBox->addItem(query.value(1).toString());
    }
    temp = QString("select count(*) from student");
    query.exec(temp);
    query.first();
    int con = query.value(0).toInt();
    ui->tableWidget->setRowCount(con);
    temp = QString("select * from student");
    query.exec(temp);
    while(query.next()){
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(query.value(3).toString()));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(query.value(4).toString()));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(query.value(5).toString()));
        i++;
    }
}

void Dialog3_2::on_comboBox_currentIndexChanged(const QString &arg1)
{
    ui->comboBox_2->clear();
    QSqlQuery query;
    QString temp;
    temp = QString("select *from class,major where class.Mid=major.Mid and Mname='%1'").arg(arg1);
    query.exec(temp);
    while(query.next()){
        ui->comboBox_2->addItem(query.value(0).toString());
    }
}

void Dialog3_2::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    refresh(arg1);
}

void Dialog3_2::refresh(QString Sclass)
{
    int i=0;
    QSqlQuery query;
    QString temp;
    temp = QString("select count(*) from student where Sclass='%1'").arg(Sclass);
    query.exec(temp);
    query.first();
    int con = query.value(0).toInt();
    ui->tableWidget->setRowCount(con);
    temp = QString("select * from student where Sclass='%1'").arg(Sclass);
    query.exec(temp);
    while(query.next()){
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(query.value(3).toString()));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(query.value(4).toString()));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(query.value(5).toString()));
        i++;
    }
}

void Dialog3_2::on_pushButton_2_clicked()   //添加学生
{
    QSqlQuery query;
    QString temp;
    temp = QString("insert into student(Sid,Sname,Ssex,Sage,Stele,Sclass)");
    temp += QString("values('%1','%2','%3','%4','%5','%6')").arg(ui->Sid->text()).arg(ui->Sname->text()).arg(ui->Ssex->text()).arg(ui->Sage->text()).arg(ui->Stele->text()).arg(ui->comboBox_2->currentText());
    bool ok = query.exec(temp);
    temp = QString("insert into idpassword(id,password,identity)");
    temp += QString("values('%1','123456','学生')").arg(ui->Sid->text());
    bool ok1 = query.exec(temp);
    if(ok&ok1){
        QMessageBox::information(this,"提示","添加成功");
        refresh(ui->comboBox_2->currentText());
    }
    else
        QMessageBox::information(this,"提示","请正确填写信息");
}

void Dialog3_2::SetStyle()
{
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"学号"<<"姓名"<<"性别"<<"年龄"<<"联系方式"<<"班级");
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //自适应宽度
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //自适应高度
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    QString pushstyle = QString("QPushButton{background-color: #63B8FF;border-style: outset;border-width: 2px;border-radius: 5px;border-color: #87CEFF;\
                                font: bold 24px;min-width:2em;color:white;font-family:华文新魏;padding: 5px;}\
                                QPushButton:hover{background-color: #48D1CC;}QPushButton:pressed {background-color: #1E90FF;border-style: inset;}\
                                QPushButton:!enabled{background-color: rgb(100, 100, 100);border-style: inset;}");
    QString linestyle = QString("QLineEdit{border-width:1px;border-radius:4px;font-size:16px;color:black;border:2px solid gray;}"
                                "QLineEdit:hover{background:#FFFACD;border-width:1px;border-radius:4px;font-size:12px;color:black;border:2px solid black;}"
                                "QLineEdit:focus{background:#FFF68F;border-width:1px;border-radius:4px;font-size:12px;color:black;border:2px solid black;}");
    ui->pushButton->setStyleSheet(pushstyle);
    ui->pushButton_2->setStyleSheet(pushstyle);
    ui->Sid->setStyleSheet(linestyle);
    ui->Sname->setStyleSheet(linestyle);
    ui->Ssex->setStyleSheet(linestyle);
    ui->Sage->setStyleSheet(linestyle);
    ui->Stele->setStyleSheet(linestyle);

}
