#ifndef DIALOG2_H
#define DIALOG2_H

#include <QDialog>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class Dialog2;
}

class Dialog2 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog2(QWidget *parent = 0);
    ~Dialog2();

private slots:
    void SetStyle();

    void receiveID2(QString ID);
    void on_pushButton_clicked();
    void init();
    void refresh();

    void on_enter_clicked();
    void enter(QString score);

    void on_score_clicked();
    QString GetRank(double score);

    void on_pushButton_2_clicked();

    bool checkenter();

private:
    Ui::Dialog2 *ui;
    QString id;
};

#endif // DIALOG2_H
