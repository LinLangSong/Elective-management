#ifndef DIALOG3_3_H
#define DIALOG3_3_H

#include <QDialog>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class Dialog3_3;
}

class Dialog3_3 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog3_3(QWidget *parent = 0);
    ~Dialog3_3();

private slots:
    void init();
    void SetStyle();
    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);
    void refresh(QString);

    void on_pushButton_2_clicked();

private:
    Ui::Dialog3_3 *ui;
};

#endif // DIALOG3_3_H
