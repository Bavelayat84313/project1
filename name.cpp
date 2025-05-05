#include "name.h"
#include "ui_name.h"
#include "page3.h"
#include "QMessageBox"

name::name(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::name)
{
    ui->setupUi(this);
}

name::~name()
{
    delete ui;
}

void name::on_pushButton_clicked()
{
    QString u1 , u2;
    u1 = ui->lineEdit->text();
    u2 = ui->lineEdit_2->text();

    if(u1=="" || u2=="")
    {
        QMessageBox::warning(this,"warning!","enter the username","ok");
    }
    else
    {
        page3 *p3 = new page3;
        p3->show();
    }
}

