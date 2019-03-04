#ifndef DIALOG3_2_H
#define DIALOG3_2_H

#include <QDialog>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class Dialog3_2;
}

class Dialog3_2 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog3_2(QWidget *parent = 0);
    ~Dialog3_2();

private slots:
    void init();
    void SetStyle();
    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_comboBox_2_currentIndexChanged(const QString &arg1);
    void refresh(QString Sclass);

    void on_pushButton_2_clicked();

private:
    Ui::Dialog3_2 *ui;
};

#endif // DIALOG3_2_H
