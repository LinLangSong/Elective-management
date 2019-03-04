#include "dialog2.h"
#include "ui_dialog2.h"

Dialog2::Dialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog2)
{
    ui->setupUi(this);
    SetStyle();
    ui->tableWidget->setColumnCount(11);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"学号"<<"姓名"<<"课程号"<<"课程名"<<"平时成绩"<<"期末成绩"<<"总成绩"<<"等级"<<"班级"<<"专业"<<"联系电话");
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //自适应宽度
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //自适应高度
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
}

Dialog2::~Dialog2()
{
    delete ui;
}

void Dialog2::receiveID2(QString ID)
{
    id = ID;
    ui->id->setText(ID);
    QSqlQuery query;
    QString temp = QString("select Tname,Tduty,Mname from teacher,major where Tid='%1' AND Tmajor=Mid").arg(ID);
    query.exec(temp);
    query.first();
    ui->name->setText(query.value(0).toString());
    ui->duty->setText(query.value(1).toString());
    ui->major->setText(query.value(2).toString());
}

void Dialog2::init()
{
    ui->comboBox->clear();
    int i=0;
    QSqlQuery query;
    QString sqltemp;
    sqltemp = QString("select Cname from course where CTid='%1'").arg(id);
    query.exec(sqltemp);
    while(query.next()){
        ui->comboBox->addItem(query.value(0).toString());
    }
    sqltemp = QString("select count(*) from student,cs,course,class,major,teacher where student.Sid=cs.Sid and Sclass=Classid and class.Mid=major.Mid and cs.Cid=course.Cid and CTid=Tid and CTid='%1'").arg(id);
    query.exec(sqltemp);
    query.first();
    int con = query.value(0).toInt();
    ui->tableWidget->setRowCount(con);
    sqltemp = QString("select student.Sid,Sname,course.Cid,Cname,uscore,fscore,score,cs.rank,Sclass,Mname,Stele from student,cs,course,class,major,teacher where student.Sid=cs.Sid and Sclass=Classid and class.Mid=major.Mid and cs.Cid=course.Cid and CTid=Tid and CTid='%1'").arg(id);
    query.exec(sqltemp);
    while(query.next()){
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(query.value(3).toString()));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(query.value(4).toString()));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(query.value(5).toString()));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(query.value(6).toString()));
        ui->tableWidget->setItem(i,7,new QTableWidgetItem(query.value(7).toString()));
        ui->tableWidget->setItem(i,8,new QTableWidgetItem(query.value(8).toString()));
        ui->tableWidget->setItem(i,9,new QTableWidgetItem(query.value(9).toString()));
        ui->tableWidget->setItem(i,10,new QTableWidgetItem(query.value(10).toString()));
        i++;
    }
}

void Dialog2::on_pushButton_clicked()
{
    refresh();
}

void Dialog2::refresh()
{
    int i=0;
    QSqlQuery query;
    QString cna = ui->comboBox->currentText();
    QString temp;
    temp = QString("select count(*) from student,cs,course,class,major,teacher where student.Sid=cs.Sid and Sclass=Classid and class.Mid=major.Mid and cs.Cid=course.Cid and CTid=Tid and CTid='%1' and Cname='%2'").arg(id).arg(cna);
    query.exec(temp);
    query.first();
    int con = query.value(0).toInt();
    ui->tableWidget->setRowCount(con);

    temp = QString("select student.Sid,Sname,course.Cid,Cname,uscore,fscore,score,cs.rank,Sclass,Mname,Stele from student,cs,course,class,major,teacher where student.Sid=cs.Sid and Sclass=Classid and class.Mid=major.Mid and cs.Cid=course.Cid and CTid=Tid and CTid='%1' and Cname='%2'").arg(id).arg(cna);
    query.exec(temp);
    while(query.next()){
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(query.value(3).toString()));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(query.value(4).toString()));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(query.value(5).toString()));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(query.value(6).toString()));
        ui->tableWidget->setItem(i,7,new QTableWidgetItem(query.value(7).toString()));
        ui->tableWidget->setItem(i,8,new QTableWidgetItem(query.value(8).toString()));
        ui->tableWidget->setItem(i,9,new QTableWidgetItem(query.value(9).toString()));
        ui->tableWidget->setItem(i,10,new QTableWidgetItem(query.value(10).toString()));
        i++;
    }
}

void Dialog2::on_enter_clicked()
{
    if(!checkenter())
        return;
    bool focus = ui->tableWidget->isItemSelected(ui->tableWidget->currentItem()); //判断是否选中一行
    if(focus){
        switch(ui->comboBox_2->currentIndex()){
        case 0:
            enter("uscore");
            break;
        case 1:
            enter("fscore");
            break;
        }
        refresh();
    }
    else
    {
        QMessageBox::information(this,"提示","选择录入成绩的学生");
    }
}

void Dialog2::enter(QString score)
{
    int row = ui->tableWidget->currentItem()->row();
    QSqlQuery query;
    QString temp;
    QString cna = ui->comboBox->currentText();
    temp = QString("select student.Sid,course.Cid from student,cs,course,class,major,teacher where student.Sid=cs.Sid and Sclass=Classid and class.Mid=major.Mid and cs.Cid=course.Cid and CTid=Tid and CTid='%1' and Cname='%2'").arg(id).arg(cna);
    query.exec(temp);
    query.first();
    for(int i=0;i<row;i++){
        query.next();
    }
    QString Sid = query.value(0).toString();
    QString Cid = query.value(1).toString();
    QString sco = ui->lineEdit->text();
    temp = QString("update cs set %1='%2' where Sid='%3' and Cid='%4'").arg(score).arg(sco).arg(Sid).arg(Cid);
    bool ok = query.exec(temp);
    if(ok){
        QMessageBox::information(this,"提示","录入成功");
    }
    else
        QMessageBox::information(this,"提示","录入失败");
}

void Dialog2::on_score_clicked()
{
    QString rank;
    QSqlQuery query,query1;
    QString temp,sqltemp;
    temp = QString("select uscore,fscore,Cid,Sid from cs");
    query.exec(temp);
    while(query.next()){
        QString cid = query.value(2).toString();
        QString sid = query.value(3).toString();
        double uscore = query.value(0).toDouble();
        double fscore = query.value(1).toDouble();
        double score = uscore*0.3+fscore*0.7;
        qDebug()<<score<<endl;
        QString sc = QString::number(score,10,2);
        qDebug()<<sc<<endl;
        rank = GetRank(score);
        sqltemp = QString("update cs set score='%1',cs.rank='%2' where Cid='%3' and Sid='%4'").arg(sc).arg(rank).arg(cid).arg(sid);
        query1.exec(sqltemp);
        query1.next();
    }
    refresh();
}

QString Dialog2::GetRank(double score)
{
    QString rank;
    if(score>90){
        rank="A";
    }
    else if(score>80)
        rank="B";
    else if(score>60)
        rank="C";
    else
        rank="D";

    return rank;
}

void Dialog2::on_pushButton_2_clicked()
{
    int i=0;
    QSqlQuery query;
    QString cna = ui->comboBox->currentText();
    QString rank = ui->comboBox_3->currentText();
    QString temp;
    temp = QString("select count(*) from student,cs,course,class,major,teacher where student.Sid=cs.Sid and Sclass=Classid and class.Mid=major.Mid and cs.Cid=course.Cid and CTid=Tid and CTid='%1' and Cname='%2' and cs.rank='%3'").arg(id).arg(cna).arg(rank);
    query.exec(temp);
    query.first();
    int con = query.value(0).toInt();
    ui->tableWidget->setRowCount(con);

    temp = QString("select student.Sid,Sname,course.Cid,Cname,uscore,fscore,score,cs.rank,Sclass,Mname,Stele from student,cs,course,class,major,teacher where student.Sid=cs.Sid and Sclass=Classid and class.Mid=major.Mid and cs.Cid=course.Cid and CTid=Tid and CTid='%1' and Cname='%2' and cs.rank='%3'").arg(id).arg(cna).arg(rank);
    query.exec(temp);
    while(query.next()){
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(query.value(3).toString()));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(query.value(4).toString()));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(query.value(5).toString()));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(query.value(6).toString()));
        ui->tableWidget->setItem(i,7,new QTableWidgetItem(query.value(7).toString()));
        ui->tableWidget->setItem(i,8,new QTableWidgetItem(query.value(8).toString()));
        ui->tableWidget->setItem(i,9,new QTableWidgetItem(query.value(9).toString()));
        ui->tableWidget->setItem(i,10,new QTableWidgetItem(query.value(10).toString()));
        i++;
    }
}

void Dialog2::SetStyle()
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
    ui->enter->setStyleSheet(pushstyle);
    ui->score->setStyleSheet(pushstyle);
    ui->lineEdit->setStyleSheet(linestyle);

}

bool Dialog2::checkenter()
{
    QSqlQuery query;
    QString temp = QString("select * from open where whether='entergrade'");
    query.exec(temp);
    query.first();
    bool ok = query.value(1).toInt();
    if(ok)
        return true;
    else{
        QMessageBox::information(this,"提示","现在不可以录入成绩");
        return false;
    }
}
