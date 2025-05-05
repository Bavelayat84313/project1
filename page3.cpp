#include "page3.h"
#include "tiles.h"
#include "ui_page3.h"
#include "QTextBrowser"
#include "QLabel"
#include <QFile>
#include <QDebug>
#include "QMessageBox"
#include <QTextStream>
#include "QGraphicsPolygonItem"
#include "QBrush"
#include "QPen"
#include "QGraphicsScene"
#include "QGraphicsView"
#include <QRandomGenerator>




page3::page3(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::page3)
{
    ui->setupUi(this);




    loadRandomMap();
    loadAndProcessMap();


}

page3::~page3()
{
    delete ui;
}






//reading a grid

QString page3::loadRandomMap() {

    const QStringList availableMaps = {

        ":/new/prefix1/grid1.txt",

        ":/new/prefix1/grid2.txt",

        ":/new/prefix1/grid3.txt",

        ":/new/prefix1/grid4.txt",

        ":/new/prefix1/grid5.txt",

        ":/new/prefix1/grid6.txt",

        ":/new/prefix1/grid7.txt",

        ":/new/prefix1/grid8.txt"

};



int randomIndex = QRandomGenerator::global()->bounded(availableMaps.size());

QString selectedPath = availableMaps.at(randomIndex);



// Show the selected index and file path

QMessageBox::information(this, "Random Map Selected",

                             QString("Index: %1\nPath: %2").arg(randomIndex).arg(selectedPath));



// Load the file

QFile file(selectedPath);

if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {

    qWarning() << "Failed to open map file:" << selectedPath;

    return QString();

}



return QTextStream(&file).readAll();

}




//process map

void page3::loadAndProcessMap() {

    QString mapContent = loadRandomMap();

    QString processedMap;

    processedMap.reserve(41);

    if(!mapContent.isEmpty()){

        int size=mapContent.size()-28;

        for(int i=0;i<size;i++){

            if(mapContent[i]=='/' && i+1 < size){

                QChar next=mapContent[i+1];

                switch (next.toLatin1()){

                case '1':

                    processedMap.append('1');

                    break;

                case '2':

                    processedMap.append('2');

                    break;

                case ' ':

                    processedMap.append('3');//for land

                    break;

                case '~':

                    processedMap.append('4');//for water

                    break;

                case '#':

                    processedMap.append('5');//for mountain

                    break;

                }

                i++;

            }

        }

    }



    tiles tilesList[41];

    int count=0;

    int i,j=0;

    while(count<41){

        i=0;

        while(i%2==0 && i<9 && j<5){

            tilesList[count].row=i;

            tilesList[count].column=j;

            tilesList[count].pic = processedMap[count].digitValue();

            i+=2;

            count++;

        }

        i=1;

        while(i%2==1 && i<9 && j<4){

            tilesList[count].row=i;

            tilesList[count].column=j;

            tilesList[count].pic = processedMap[count].digitValue();

            i+=2;

            count++;

        }

        j++;

    }



    QVector<QLabel*> labels = {//for 1st map

                ui->label_a1, ui->label_a3, ui->label_a5,ui->label_a7,ui->label_a9,

                ui->label_a2, ui->label_a4, ui->label_a6,ui->label_a8,

                ui->label_b1, ui->label_b3, ui->label_b5,ui->label_b7,ui->label_b9,

                ui->label_b2, ui->label_b4, ui->label_b6,ui->label_b8,

                ui->label_c1, ui->label_c3, ui->label_c5,ui->label_c7,ui->label_c9,

                ui->label_c2, ui->label_c4, ui->label_c6,ui->label_c8,

                ui->label_d1, ui->label_d3, ui->label_d5,ui->label_d7,ui->label_d9,

                ui->label_d2, ui->label_d4, ui->label_d6,ui->label_d8,

                ui->label_e1, ui->label_e3, ui->label_e5,ui->label_e7,ui->label_e9,

                };


    for(i=0;i<41;i++){

        if(tilesList[i].pic==1){//p1 land red

            labels[i]->setStyleSheet("background-color:cyan;");
        }

        else if(tilesList[i].pic==2){//p2 land blue

            labels[i]->setStyleSheet("background-color:pink;");

        }

        else if(tilesList[i].pic==3){//normal land

            labels[i]->setStyleSheet("background-color:yellow;");


        }

        else if(tilesList[i].pic==4){//water

            labels[i]->setStyleSheet("background-color: blue;");


        }

        else if(tilesList[i].pic==5){//mountain

            labels[i]->setStyleSheet("background-color:brown;");


        }

    }



}


//


void page3::on_pushButton_3_clicked()
{
    QString a = ui->lineEdit->text();
    bool ok;
    int b = a.toInt(&ok);
    switch (b){
    case 1:
        ui->label_a1->setText("_agent1");
        break;
    case 2:
        ui->label_b1->setText("_agent1");
        break;
    case 3:
        ui->label_c1->setText("_agent1");
        break;
    case 4:
        ui->label_d1->setText("_agent1");
        break;
    case 5:
        ui->label_e1->setText("_agent1");
        break;
    case 6:
        ui->label_a2->setText("_agent1");
        break;
    case 7:
        ui->label_b2->setText("_agent1");
        break;
    case 8:
        ui->label_c2->setText("_agent1");
        break;
    case 9:
        ui->label_d2->setText("_agent1");
        break;
    case 10:
        ui->label_a3->setText("_agent1");
        break;
    case 11:
        ui->label_b3->setText("_agent1");
        break;
    case 12:
        ui->label_c3->setText("_agent1");
        break;
    case 13:
        ui->label_d3->setText("_agent1");
        break;
    case 14:
        ui->label_e3->setText("_agent1");
        break;
    case 15:
        ui->label_a4->setText("_agent1");
        break;
    case 16:
        ui->label_b4->setText("_agent1");
        break;
    case 17:
        ui->label_c4->setText("_agent1");
        break;
    case 18:
        ui->label_d4->setText("_agent1");
        break;
    }

}
