#include "dialog3_1.h"
#include "ui_dialog3_1.h"

Dialog3_1::Dialog3_1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog3_1)
{
    ui->setupUi(this);
    SetStyle();
}

Dialog3_1::~Dialog3_1()
{
    delete ui;
}

void Dialog3_1::on_pushButton_2_clicked()  //添加教师
{
    QSqlQuery query;
    QString temp;
    temp = QString("select * from major where Mname='%1'").arg(ui->comboBox->currentText());
    query.exec(temp);query.first();
    QString major = query.value(0).toString();
    temp = QString("insert into teacher(Tid,Tname,Tsex,Tmajor,Tduty)");
    temp += QString("values('%1','%2','%3','%4','%5')").arg(ui->Tid->text()).arg(ui->Tname->text()).arg(ui->Tsex->text()).arg(major).arg(ui->Tduty->text());
    bool ok = query.exec(temp);
    temp = QString("insert into idpassword(id,password,identity)");
    temp += QString("values('%1','12345','教师')").arg(ui->Tid->text());
    bool ok1 = query.exec(temp);
    if(ok&ok1){
        QMessageBox::information(this,"提示","添加成功");
        refresh(ui->comboBox->currentText());
    }
    else
        QMessageBox::information(this,"提示","请正确填写信息");
}

void Dialog3_1::init()
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
    temp = QString("select count(*) from teacher");
    query.exec(temp);
    query.first();
    int con = query.value(0).toInt();
    ui->tableWidget->setRowCount(con);
    temp = QString("select * from teacher,major where Tmajor=Mid");
    query.exec(temp);
    while(query.next()){
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(query.value(6).toString()));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(query.value(4).toString()));
        i++;
    }
}

void Dialog3_1::on_comboBox_currentIndexChanged(const QString &arg1)
{
    refresh(arg1);
}

void Dialog3_1::refresh(QString major)
{
    int i=0;
    QSqlQuery query;
    QString temp;
    temp = QString("select count(*) from teacher,major where Tmajor=Mid and Mname='%1'").arg(major);
    query.exec(temp);
    query.first();
    int con = query.value(0).toInt();
    ui->tableWidget->setRowCount(con);
    temp = QString("select * from teacher,major where Tmajor=Mid and Mname='%1'").arg(major);
    query.exec(temp);
    while(query.next()){
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(query.value(6).toString()));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(query.value(4).toString()));
        i++;
    }
}

void Dialog3_1::on_pushButton_clicked()  //删除教师
{
    QString major = ui->comboBox->currentText();
    bool focus = ui->tableWidget->isItemSelected(ui->tableWidget->currentItem()); //判断是否选中一行
    if(focus){
        int row = ui->tableWidget->currentItem()->row();
        qDebug()<<row<<endl;
        QSqlQuery query;
        QString sqltemp;
        sqltemp = QString("select Tid from teacher,major where Tmajor=Mid and Mname='%1'").arg(major);
        query.exec(sqltemp);
        query.first();
        for(int i=1;i<=row;i++){
            query.next();
        }
        QString Tid = query.value(0).toString();

        sqltemp = QString("delete from cs where Cid in (select Cid from course,teacher where Tid='%1' and CTid=Tid)").arg(Tid);
        bool ok1 = query.exec(sqltemp);    //删除教师所教被选课程
        sqltemp = QString("delete from course where CTid='%1'").arg(Tid);
        bool ok2 = query.exec(sqltemp);    //删除教师所教课程
        sqltemp = QString("delete from teacher where Tid='%1'").arg(Tid);
        bool ok3 = query.exec(sqltemp);   //删除教师信息
        sqltemp = QString("delete from idpassword where id='%1'").arg(Tid);
        bool ok4 = query.exec(sqltemp);   //删除登录信息

        if(ok1&&ok2&&ok3&&ok4){
            QMessageBox::information(this,"提示","删除成功");
        }
        else
            QMessageBox::information(this,"提示","删除");
        refresh(ui->comboBox->currentText());

    }
    else
        QMessageBox::information(this,"提示","请选择一位老师");
}

void Dialog3_1::SetStyle()
{
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"教师号"<<"教师姓名"<<"性别"<<"专业"<<"职务");
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
    ui->Tid->setStyleSheet(linestyle);
    ui->Tname->setStyleSheet(linestyle);
    ui->Tsex->setStyleSheet(linestyle);
    ui->Tduty->setStyleSheet(linestyle);
}
