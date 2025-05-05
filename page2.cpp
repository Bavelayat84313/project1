#include "page2.h"
#include "ui_page2.h"
#include "gallery.h"
#include "name.h"

page2::page2(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::page2)
{
    ui->setupUi(this);
}

page2::~page2()
{
    delete ui;
}

void page2::on_pushButton_clicked()
{
    gallery *g = new gallery;
    g->show();
}


void page2::on_pushButton_2_clicked()
{
    name *n = new name;
    n->show();
}

