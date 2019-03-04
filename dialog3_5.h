#ifndef DIALOG3_5_H
#define DIALOG3_5_H

#include <QDialog>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class Dialog3_5;
}

class Dialog3_5 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog3_5(QWidget *parent = 0);
    ~Dialog3_5();

private slots:
    void init();
    void refresh();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void SetStyle();

private:
    Ui::Dialog3_5 *ui;
};

#endif // DIALOG3_5_H
