#include "dialog3_4.h"
#include "ui_dialog3_4.h"

Dialog3_4::Dialog3_4(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog3_4)
{
    ui->setupUi(this);
    SetStyle();
}

Dialog3_4::~Dialog3_4()
{
    delete ui;
}

void Dialog3_4::on_pushButton_clicked()   //删除专业
{
    bool focus = ui->tableWidget->isItemSelected(ui->tableWidget->currentItem()); //判断是否选中一行
    if(focus){
        int row = ui->tableWidget->currentItem()->row();
        QSqlQuery query;
        QString sqltemp;
        sqltemp = QString("select * from major");
        query.exec(sqltemp);
        query.first();
        for(int i=1;i<=row;i++){
            query.next();
        }
        QString Mid = query.value(0).toString();

        sqltemp = QString("delete from class where Mid='%1'").arg(Mid);
        bool ok1 = query.exec(sqltemp);    //删除相关班级
        sqltemp = QString("delete from teacher where Tmajor='%1'").arg(Mid);
        bool ok2 = query.exec(sqltemp);    //删除相关教师
        sqltemp = QString("delete from course where Cmajor='%1'").arg(Mid);
        bool ok4 = query.exec(sqltemp);  //删除相关课程
        sqltemp = QString("delete from major where Mid='%1'").arg(Mid);
        bool ok3 = query.exec(sqltemp);  //删除专业
        if(ok1&&ok2&&ok3&&ok4){
            QMessageBox::information(this,"提示","删除成功");
            major_refresh();
            class_init();
        }
        else
            QMessageBox::information(this,"提示","删除失败");
    }
    else
        QMessageBox::information(this,"提示","请选择一个专业");
}

void Dialog3_4::on_pushButton_2_clicked()   //添加专业
{
    QSqlQuery query;
    QString temp;
    temp = QString("insert into major(Mid,Mname)");
    temp += QString("values('%1','%2')").arg(ui->Mid->text()).arg(ui->Mname->text());
    bool ok = query.exec(temp);
    if(ok){
        QMessageBox::information(this,"提示","添加成功");
        major_refresh();
        class_init();
    }
    else
        QMessageBox::information(this,"提示","请正确填写信息");
}

void Dialog3_4::init()
{
    major_refresh();
    class_init();
}

void Dialog3_4::class_init()  //班级初始化
{
    ui->comboBox->clear();
    int i=0;
    QSqlQuery query;
    QString temp;
    temp = QString("select * from major");
    query.exec(temp);
    while(query.next()){
        ui->comboBox->addItem(query.value(1).toString());
    }
    temp = QString("select count(*) from class,major where class.Mid=major.Mid");
    query.exec(temp);
    query.first();
    int con = query.value(0).toInt();
    ui->tableWidget_2->setRowCount(con);
    temp = QString("select Classid,grade,Mname from class,major where class.Mid=major.Mid");
    query.exec(temp);
    while(query.next()){
        ui->tableWidget_2->setItem(i,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget_2->setItem(i,1,new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget_2->setItem(i,2,new QTableWidgetItem(query.value(2).toString()));
        i++;
    }
}

void Dialog3_4::major_refresh()
{
    int i=0;
    QSqlQuery query;
    QString temp;
    temp = QString("select count(*) from major");
    query.exec(temp);
    query.first();
    int con = query.value(0).toInt();
    ui->tableWidget->setRowCount(con);
    temp = QString("select * from major");
    query.exec(temp);
    while(query.next()){
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(query.value(1).toString()));
        i++;
    }
}

void Dialog3_4::class_refresh(QString major)
{
    int i=0;
    QSqlQuery query;
    QString temp;
    temp = QString("select count(*) from class,major where class.Mid=major.Mid and Mname='%1'").arg(major);
    query.exec(temp);
    query.first();
    int con = query.value(0).toInt();
    ui->tableWidget_2->setRowCount(con);
    temp = QString("select Classid,grade,Mname from class,major where class.Mid=major.Mid and Mname='%1'").arg(major);
    query.exec(temp);
    while(query.next()){
        ui->tableWidget_2->setItem(i,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget_2->setItem(i,1,new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget_2->setItem(i,2,new QTableWidgetItem(query.value(2).toString()));
        i++;
    }
}

void Dialog3_4::on_comboBox_currentIndexChanged(const QString &arg1)  //班级下拉框改变
{
    class_refresh(arg1);
}

void Dialog3_4::on_pushButton_4_clicked()   //添加班级
{
    QSqlQuery query;
    QString temp;
    temp = QString("select * from major where Mname='%1'").arg(ui->comboBox->currentText());
    query.exec(temp);query.first();
    QString major = query.value(0).toString();
    temp = QString("insert into class(Classid,grade,Mid)");
    temp += QString("values('%1','%2','%3')").arg(ui->Cid->text()).arg(ui->grade->text()).arg(major);
    bool ok = query.exec(temp);
    if(ok){
        QMessageBox::information(this,"提示","添加成功");
        class_refresh(ui->comboBox->currentText());
    }
    else
        QMessageBox::information(this,"提示","请正确填写信息");
}

void Dialog3_4::on_pushButton_3_clicked()  //删除班级
{
    QString major = ui->comboBox->currentText();
    bool focus = ui->tableWidget_2->isItemSelected(ui->tableWidget_2->currentItem()); //判断是否选中一行
    if(focus){
        int row = ui->tableWidget_2->currentItem()->row();
        qDebug()<<row<<endl;
        QSqlQuery query;
        QString sqltemp;
        sqltemp = QString("select Classid from class,major where class.Mid=major.Mid and Mname='%1'").arg(major);
        query.exec(sqltemp);
        query.first();
        for(int i=1;i<=row;i++){
            query.next();
        }
        QString Classid = query.value(0).toString();

        sqltemp = QString("delete from student where Sclass='%1'").arg(Classid);
        bool ok1 = query.exec(sqltemp);    //删除班级中所有学生
        sqltemp = QString("delete from class where Classid='%1'").arg(Classid);
        bool ok2 = query.exec(sqltemp);    //删除班级信息
        if(ok1&&ok2){
            QMessageBox::information(this,"提示","删除成功");
        }
        else
            QMessageBox::information(this,"提示","删除");
        class_refresh(ui->comboBox->currentText());

    }
    else
        QMessageBox::information(this,"提示","请选择一个班级");
}

void Dialog3_4::SetStyle()
{
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"专业编号"<<"专业名称");
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //自适应宽度
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //自适应高度
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_2->setColumnCount(3);
    ui->tableWidget_2->setHorizontalHeaderLabels(QStringList()<<"班级编号"<<"年级"<<"所属专业");
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //自适应宽度
    ui->tableWidget_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //自适应高度
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_2->setSelectionMode(QAbstractItemView::SingleSelection);
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
    ui->Cid->setStyleSheet(linestyle);
    ui->grade->setStyleSheet(linestyle);
    ui->Mid->setStyleSheet(linestyle);
    ui->Mname->setStyleSheet(linestyle);


}
