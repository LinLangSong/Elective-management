#ifndef DIALOG1_1_H
#define DIALOG1_1_H

#include <QDialog>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class Dialog1_1;
}

class Dialog1_1 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog1_1(QWidget *parent = 0);
    ~Dialog1_1();

private slots:
    void SetStyle();
    void receiveID1_1(QString ID);
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Dialog1_1 *ui;
    QString id;
};

#endif // DIALOG1_1_H
