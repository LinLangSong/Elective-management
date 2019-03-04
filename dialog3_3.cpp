#include "dialog3_3.h"
#include "ui_dialog3_3.h"

Dialog3_3::Dialog3_3(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog3_3)
{
    ui->setupUi(this);
    SetStyle();
}

Dialog3_3::~Dialog3_3()
{
    delete ui;
}

void Dialog3_3::on_pushButton_clicked()   //删除课程
{
    bool focus = ui->tableWidget->isItemSelected(ui->tableWidget->currentItem()); //判断是否选中一行
    if(focus){
        int row = ui->tableWidget->currentItem()->row();
        QSqlQuery query;
        QString sqltemp;
        sqltemp = QString("select Cid from teacher,major,course where CTid=Tid and Cmajor=Mid and Mname='%1'").arg(ui->comboBox->currentText());
        query.exec(sqltemp);
        query.first();
        for(int i=1;i<=row;i++){
            query.next();
        }
        QString Cid = query.value(0).toString();

        sqltemp = QString("delete from cs where Cid='%1'").arg(Cid);
        bool ok1 = query.exec(sqltemp);    //删除选课表里课程信息
        sqltemp = QString("delete from course where Cid='%1'").arg(Cid);
        bool ok2 = query.exec(sqltemp);    //删除课程表里的对应课程
        if(ok1&&ok2){
            QMessageBox::information(this,"提示","删除成功");
        }
        else
            QMessageBox::information(this,"提示","删除");
        refresh(ui->comboBox->currentText());

    }
    else
        QMessageBox::information(this,"提示","请选择一位学生");
}

void Dialog3_3::init()
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
    temp = QString("select * from teacher");
    query.exec(temp);
    while(query.next()){
        ui->comboBox_2->addItem(query.value(0).toString());
    }
    temp = QString("select count(*) from course");
    query.exec(temp);
    query.first();
    int con = query.value(0).toInt();
    ui->tableWidget->setRowCount(con);
    temp = QString("select Cid,Cname,Chour,Cscore,Tname,Mname from teacher,major,course where CTid=Tid and Cmajor=Mid");
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

void Dialog3_3::on_comboBox_currentIndexChanged(const QString &arg1)  //根据下拉框选择专业显示对应课程
{
    refresh(arg1);
}

void Dialog3_3::refresh(QString major)
{
    int i=0;
    QSqlQuery query;
    QString temp;
    temp = QString("select count(*) from course,major where Cmajor=Mid and Mname='%1'").arg(major);
    query.exec(temp);
    query.first();
    int con = query.value(0).toInt();
    ui->tableWidget->setRowCount(con);
    temp = QString("select Cid,Cname,Chour,Cscore,Tname,Mname from teacher,major,course where CTid=Tid and Cmajor=Mid and Mname='%1'").arg(major);
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

void Dialog3_3::on_pushButton_2_clicked()  //添加课程
{
    QSqlQuery query;
    QString temp;
    temp = QString("select * from major where Mname='%1'").arg(ui->comboBox->currentText());
    query.exec(temp);query.first();
    QString major = query.value(0).toString();
    temp = QString("insert into course(Cid,Cname,Chour,Cscore,CTid,Cmajor)");
    temp += QString("values('%1','%2','%3','%4','%5','%6')").arg(ui->Cid->text()).arg(ui->Cname->text()).arg(ui->Chour->text()).arg(ui->Cscore->text()).arg(ui->comboBox_2->currentText()).arg(major);
    bool ok = query.exec(temp);
    if(ok){
        QMessageBox::information(this,"提示","添加成功");
        refresh(ui->comboBox->currentText());
    }
    else
        QMessageBox::information(this,"提示","请正确填写信息");
}

void Dialog3_3::SetStyle()
{
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"课程号"<<"课程名"<<"学时"<<"学分"<<"教师"<<"专业");
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
    ui->Cid->setStyleSheet(linestyle);
    ui->Cname->setStyleSheet(linestyle);
    ui->Chour->setStyleSheet(linestyle);
    ui->Cscore->setStyleSheet(linestyle);
}
