#include "dialog1.h"
#include "ui_dialog1.h"

Dialog1::Dialog1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog1)
{
    ui->setupUi(this);
    connect(this,SIGNAL(sendID1_1(QString)),&dialog1_1,SLOT(receiveID1_1(QString)));
    SetStyle();
    flagfind = 0;

}

Dialog1::~Dialog1()
{
    delete ui;
}

void Dialog1::on_pushButton_clicked()  //展示已选课程
{
    flag = 0;
    pushButton();
}

void Dialog1::pushButton()
{
    int i=0;
    QSqlQuery query;
    QString sqltemp = QString("select count(*) from cs,course,teacher where Sid='%1' AND cs.Cid=course.Cid AND CTid=Tid").arg(id);
    query.exec(sqltemp);
    query.first();
    int con = query.value(0).toInt();
    ui->tableWidget->setRowCount(con);

    sqltemp = QString("select cs.Cid,Cname,Chour,Cscore,Tname,score from cs,course,teacher where Sid='%1' AND cs.Cid=course.Cid AND CTid=Tid").arg(id);
    query.exec(sqltemp);
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

void Dialog1::receiveID1(QString ID)
{
    id = ID;
    ui->id->setText(ID);
    QString name,Sclass,major;
    QSqlQuery query;
    QString temp = QString("select Sname,Classid,Mname from student,class,major where Sid = '%1' AND student.Sclass=class.Classid AND class.Mid=major.Mid").arg(ID);
    query.exec(temp);
    query.first();
    name = query.value(0).toString();
    Sclass = query.value(1).toString();
    major =  query.value(2).toString();
    ui->name->setText(name);
    ui->class_2->setText(Sclass);
    ui->major->setText(major);
}

void Dialog1::on_pushButton_2_clicked()  //展示可选课程
{
    flag =1;
    pushButton2();
}

void Dialog1::pushButton2()
{
    int i=0;
    QSqlQuery query;
    QString sqltemp = QString("select count(*) from course,teacher where CTid=teacher.Tid AND Cid not in (select cs.Cid from cs where Sid='%1')").arg(id);
    query.exec(sqltemp);
    query.first();
    int con = query.value(0).toInt();
    ui->tableWidget->setRowCount(con);

    sqltemp = QString("select Cid,Cname,Chour,Cscore,Tname from course,teacher where CTid=teacher.Tid AND Cid not in (select cs.Cid from cs where Sid='%1')").arg(id);
    query.exec(sqltemp);
    while(query.next()){
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(query.value(3).toString()));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(query.value(4).toString()));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem("0"));
        i++;
    }
}

void Dialog1::on_pushButton_3_clicked()  //添加未选课程
{
    if(!checkchoose())
        return;
    if(!flag){
        QMessageBox::information(this,"提示","您所选的为已选课程，无法再次添加");
        return;
    }
    bool focus = ui->tableWidget->isItemSelected(ui->tableWidget->currentItem()); //判断是否选中一行
    if(focus){
        int row = ui->tableWidget->currentItem()->row();
        qDebug()<<row<<endl;
        QSqlQuery query;
        QString sqltemp;
        if(flagfind){
            sqltemp = findstr;
        }
        else
            sqltemp = QString("select Cid,Cname,Chour,Cscore,Tname from course,teacher where CTid=teacher.Tid AND Cid not in (select cs.Cid from cs where Sid='%1')").arg(id);

        query.exec(sqltemp);
        query.first();
        for(int i=1;i<=row;i++){
            query.next();
        }
        QString Cid = query.value(0).toString();

        sqltemp = QString("insert into cs(Sid,Cid)");
        sqltemp += QString("values('%1','%2')").arg(id).arg(Cid);
        bool ok = query.exec(sqltemp);
        if(ok){
            QMessageBox::information(this,"提示","添加课程成功");
        }
        else
            QMessageBox::information(this,"提示","添加课程失败");
        pushButton2();
    }
    else
        QMessageBox::information(this,"提示","请选择一门课程进行添加");
}




void Dialog1::on_pushButton_4_clicked()  //删除已选课程
{
    if(!checkchoose())
        return;
    if(flag){
        QMessageBox::information(this,"提示","您尚未选修该课程，无法退选");
        return ;
    }
    bool focus = ui->tableWidget->isItemSelected(ui->tableWidget->currentItem()); //判断是否选中一行
    if(focus){
        int row = ui->tableWidget->currentItem()->row();
        qDebug()<<row<<endl;
        QSqlQuery query;
        QString sqltemp;
        if(flagfind){
            sqltemp = findstr;
        }
        else
            sqltemp = QString("select cs.Cid,Cname,Chour,Cscore,Tname,score from cs,course,teacher where Sid='%1' AND cs.Cid=course.Cid AND CTid=Tid").arg(id);
        query.exec(sqltemp);
        query.first();
        for(int i=0;i<row;i++){
            query.next();
        }
        QString Cid = query.value(0).toString();

        sqltemp = QString("delete from cs where Sid='%1' AND Cid='%2'").arg(id).arg(Cid);
        bool ok = query.exec(sqltemp);
        if(ok){
            QMessageBox::information(this,"提示","退选课程成功");
        }
        else
            QMessageBox::information(this,"提示","退选课程失败");
        pushButton();
    }
    else
        QMessageBox::information(this,"提示","请选择一门课程进行退选");
}

void Dialog1::on_pushButton_5_clicked()
{
    switch(ui->comboBox->currentIndex()){
    case 0:
        findby("cs.Cid");
        break;
    case 1:
        findby("Cname");
        break;
    case 2:
        findby("Chour");
        break;
    case 3:
        findby("Cscore");
        break;
    case 4:
        findby("Tname");
        break;
    };

}

void Dialog1::findby(QString sty)
{
    flagfind = 1;
    int i=0;
    QSqlQuery query;
    QString sqltemp;
    QString find = ui->findtext->text();
    if(flag){
        sqltemp = QString("select count(*) from course,teacher where %1='%2' AND CTid=teacher.Tid AND Cid not in (select cs.Cid from cs where Sid='%3')").arg(sty).arg(find).arg(id);
        query.exec(sqltemp);
        query.first();
        int con = query.value(0).toInt();
        ui->tableWidget->setRowCount(con);

        findstr = sqltemp = QString("select Cid,Cname,Chour,Cscore,Tname from course,teacher where %1='%2' AND CTid=teacher.Tid AND Cid not in (select cs.Cid from cs where Sid='%3')").arg(sty).arg(find).arg(id);
        query.exec(sqltemp);
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
    else{
        sqltemp = QString("select count(*) from cs,course,teacher where %1='%2' AND Sid='%3' AND cs.Cid=course.Cid AND CTid=Tid").arg(sty).arg(find).arg(id);
        query.exec(sqltemp);
        query.first();
        int con = query.value(0).toInt();
        ui->tableWidget->setRowCount(con);

        findstr = sqltemp = QString("select cs.Cid,Cname,Chour,Cscore,Tname,score from cs,course,teacher where %1='%2' AND Sid='%3' AND cs.Cid=course.Cid AND CTid=Tid").arg(sty).arg(find).arg(id);
        query.exec(sqltemp);
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
}

void Dialog1::SetStyle()
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
    ui->pushButton_3->setStyleSheet(pushstyle);
    ui->pushButton_4->setStyleSheet(pushstyle);
    ui->pushButton_5->setStyleSheet(pushstyle);
    ui->pushButton_6->setStyleSheet(pushstyle);
    ui->findtext->setStyleSheet(linestyle);
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"课程号"<<"课程名"<<"学时"<<"学分"<<"教师"<<"分数");
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //自适应宽度
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //自适应高度
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

}

void Dialog1::on_pushButton_6_clicked()
{
    emit sendID1_1(ui->id->text());
    //dialog1_1.show();
    dialog1_1.exec();
}

bool Dialog1::checkchoose()
{
     QSqlQuery query;
     QString temp = QString("select * from open where whether='choosecourse'");
     query.exec(temp);
     query.first();
     bool ok = query.value(1).toInt();
     if(ok)
         return true;
     else{
         QMessageBox::information(this,"提示","现在不可以修改课程");
         return false;
     }
}
