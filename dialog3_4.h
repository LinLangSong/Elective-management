#ifndef DIALOG3_4_H
#define DIALOG3_4_H

#include <QDialog>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class Dialog3_4;
}

class Dialog3_4 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog3_4(QWidget *parent = 0);
    ~Dialog3_4();

private slots:
    void init();
    void on_pushButton_clicked();
    void major_refresh();
    void class_refresh(QString);
    void class_init();

    void on_pushButton_2_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void SetStyle();

private:
    Ui::Dialog3_4 *ui;
};

#endif // DIALOG3_4_H
