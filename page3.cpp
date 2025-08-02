#include "page3.h"
#include "tiles.h"
#include "ui_page3.h"
#include "QTextBrowser"
#include "QLabel"
#include "QPushButton"
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
#include <QString>


tiles tilesList[41];

page3::page3(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::page3)
{
    ui->setupUi(this);

    pushButtons = {

        ui->pushButton_4, ui->pushButton_5, ui->pushButton_6,ui->pushButton_7,ui->pushButton_8,

        ui->pushButton_9, ui->pushButton_10, ui->pushButton_11,ui->pushButton_12,

        ui->pushButton_13, ui->pushButton_14, ui->pushButton_15,ui->pushButton_16,ui->pushButton_17,

        ui->pushButton_18, ui->pushButton_19, ui->pushButton_20,ui->pushButton_21,

        ui->pushButton_22, ui->pushButton_23, ui->pushButton_24,ui->pushButton_25,ui->pushButton_26,

        ui->pushButton_27, ui->pushButton_28, ui->pushButton_29,ui->pushButton_30,

        ui->pushButton_31, ui->pushButton_32, ui->pushButton_33,ui->pushButton_34,ui->pushButton_35,

        ui->pushButton_36, ui->pushButton_37, ui->pushButton_38,ui->pushButton_39,

        ui->pushButton_40, ui->pushButton_41, ui->pushButton_42,ui->pushButton_43,ui->pushButton_44,

    };

    charactersplayer1 = {

        ui->billy1, ui->reketon1, ui->angus1, ui->duraham1, ui->colonelbaba1, ui->medusa1, ui->bunka1, ui->sanka1,

        ui->sirlamorak1, ui->kabu1, ui->rajakal1, ui->salih1, ui->khan1, ui->boi1, ui->eloi1, ui->kanar1,

        ui->elsa1, ui->karissa1, ui->sirphilip1, ui->frost1, ui->tusk1, ui->rambo1, ui->sabrina1, ui->death1

    };

    charactersplayer2 = {

        ui->billy2, ui->reketon2, ui->angus2, ui->duraham2, ui->colonelbaba2, ui->medusa2, ui->bunka2, ui->sanka2,

        ui->sirlamorak2, ui->kabu2, ui->rajakal2, ui->salih2, ui->khan2, ui->boi2, ui->eloi2, ui->kanar2,

        ui->elsa2, ui->karissa2, ui->sirphilip2, ui->frost2, ui->tusk2, ui->rambo2, ui->sabrina2, ui->death2

    };

    loadRandomMap();
    loadAndProcessMap();

    onCharacterClicked();
    onBoardClicked();

    for (QPushButton* btn : charactersplayer1) {
        connect(btn, &QPushButton::clicked, this, &page3::onCharacterClicked);
    }

    for (QPushButton* btn : charactersplayer2) {
        connect(btn, &QPushButton::clicked, this, &page3::onCharacterClicked);
    }

    for (QPushButton* btn : pushButtons) {
        connect(btn, &QPushButton::clicked, this, &page3::onBoardClicked);
    }

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




    for(i=0;i<41;i++){
        pushButtons[i]->setStyleSheet("border:1px solid black;");

        if(tilesList[i].pic==1){//p1 land red

            pushButtons[i]->setStyleSheet("background-color:cyan;");
        }

        else if(tilesList[i].pic==2){//p2 land blue

            pushButtons[i]->setStyleSheet("background-color:pink;");

        }

        else if(tilesList[i].pic==3){//normal land

            pushButtons[i]->setStyleSheet("background-color:yellow;");


        }

        else if(tilesList[i].pic==4){//water

            pushButtons[i]->setStyleSheet("background-color: blue;");


        }

        else if(tilesList[i].pic==5){//mountain

            pushButtons[i]->setStyleSheet("background-color:brown;");


        }

    }

}



void page3::onCharacterClicked() {

    QPushButton* clickedBtn = qobject_cast<QPushButton*>(sender());

    if (!clickedBtn) {
        qDebug() << "Sender is invalid!";
        return;
    }

    /*if (selectedCharacter) {
        selectedCharacter->setStyleSheet("");// حذف حاشیه زرد
    }*/

    if (isPlayer1Turn && charactersplayer1.contains(clickedBtn)) {
        selectedCharacter = clickedBtn;
        clickedBtn->setStyleSheet("background-color: yellow;");
    }
    else if (!isPlayer1Turn && charactersplayer2.contains(clickedBtn)) {
        selectedCharacter = clickedBtn;
        clickedBtn->setStyleSheet("background-color: yellow;");
    }

    //selectedCharacter = clickedBtn;
    //isCharacterSelected = true;

    //clickedBtn->setStyleSheet("border: 2px solid yellow;");

}


void page3::onBoardClicked() {

    if (!selectedCharacter) {
        qDebug() << "No character selected!";
        return;
    }

    QPushButton* targetBtn = qobject_cast<QPushButton*>(sender());

    if (!targetBtn) {
        qDebug() << "Target button is invalid!";
        return;
    }

    int tileIndex = pushButtons.indexOf(targetBtn);
    if (tileIndex == -1) {
        qDebug() << "Target button not found in tiles list!";
        return;
    }

    if (isPlayer1Turn && tilesList[tileIndex].pic != 1) {
        QMessageBox::warning(this, "خطا", "بازیکن ۱ فقط می‌تواند در زمین‌های آبی کاراکتر قرار دهد!");
        return;
    }
    else if (!isPlayer1Turn && tilesList[tileIndex].pic != 2) {
        QMessageBox::warning(this, "خطا", "بازیکن ۲ فقط می‌تواند در زمین‌های صورتی کاراکتر قرار دهد!");
        return;
    }

    //targetBtn->setStyleSheet(selectedCharacter->styleSheet());

    targetBtn->setIcon(selectedCharacter->icon());
    //targetBtn->setText(selectedCharacter->text());

    selectedCharacter->setIcon(QIcon());
    //selectedCharacter->setText("");

    //selectedCharacter->setStyleSheet("");

    if (isPlayer1Turn) {
        player1CharacterCount++;
        if (player1CharacterCount >= 5) {
            for(QPushButton* btn : charactersplayer1){
                btn->setEnabled(false);
            }
            isPlayer1Turn = false; // تغییر نوبت به بازیکن ۲
            qDebug() << "نوبت بازیکن ۲";
        }
    }
    else {
        player2CharacterCount++;
        if (player2CharacterCount >= 5) {
            for(QPushButton* btn : charactersplayer2){
                btn->setEnabled(false);
            }
            isPlayer1Turn = true; // تغییر نوبت به بازیکن ۱
            qDebug() << "نوبت بازیکن ۱";
        }
    }

    selectedCharacter = nullptr;
    //isCharacterSelected = false;
}


