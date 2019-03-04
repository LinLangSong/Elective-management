#ifndef DIALOG3_H
#define DIALOG3_H

#include <QDialog>
#include "dialog3_1.h"
#include "dialog3_2.h"
#include "dialog3_3.h"
#include "dialog3_4.h"
#include "dialog3_5.h"

namespace Ui {
class Dialog3;
}

class Dialog3 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog3(QWidget *parent = 0);
    ~Dialog3();

signals:
    void teacher();
    void student();
    void course();
    void major();
    void oc();
private slots:
    void init();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Dialog3 *ui;
    Dialog3_1 dialog3_1;
    Dialog3_2 dialog3_2;
    Dialog3_3 dialog3_3;
    Dialog3_4 dialog3_4;
    Dialog3_5 dialog3_5;
};

#endif // DIALOG3_H
