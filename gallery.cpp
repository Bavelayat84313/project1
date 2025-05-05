#include "gallery.h"
#include "ui_gallery.h"
#include "page2.h"

gallery::gallery(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gallery)
{
    ui->setupUi(this);
}

gallery::~gallery()
{
    delete ui;
}




void gallery::on_pushButton_clicked()
{
    page2 *p2 = new page2;
    p2->show();
}

