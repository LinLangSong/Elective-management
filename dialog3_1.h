#ifndef DIALOG3_1_H
#define DIALOG3_1_H

#include <QDialog>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class Dialog3_1;
}

class Dialog3_1 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog3_1(QWidget *parent = 0);
    ~Dialog3_1();

private slots:
    void init();
    void SetStyle();
    void on_pushButton_2_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);
    void refresh(QString major);

    void on_pushButton_clicked();

private:
    Ui::Dialog3_1 *ui;
};

#endif // DIALOG3_1_H
