#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include "dialog1.h"
#include "dialog2.h"
#include "dialog3.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool sqlconnect(const QString dbname);

signals:
    void sendID1(QString);
    void sendID2(QString);
    void sendID3();

private slots:
    void SetStyle();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    bool check();

private:
    Ui::MainWindow *ui;
    Dialog1 dialog1;
    Dialog2 dialog2;
    Dialog3 dialog3;
};

#endif // MAINWINDOW_H
