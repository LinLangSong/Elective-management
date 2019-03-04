#ifndef DIALOG1_H
#define DIALOG1_H

#include <QDialog>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>

#include "dialog1_1.h"

namespace Ui {
class Dialog1;
}

class Dialog1 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog1(QWidget *parent = 0);
    ~Dialog1();

private slots:
    void SetStyle();

    void on_pushButton_clicked();
    void pushButton();
    void receiveID1(QString ID);

    void on_pushButton_2_clicked();
    void pushButton2();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();
    void findby(QString sty);

    void on_pushButton_6_clicked();
    bool checkchoose();

signals:
    void sendID1_1(QString);
private:
    Ui::Dialog1 *ui;
    Dialog1_1 dialog1_1;
    QString id;
    bool flag;  //记录显示的是已选课程1还是未选课程0
    bool flagfind;//记录是否查找过
    QString findstr;
};

#endif // DIALOG1_H
