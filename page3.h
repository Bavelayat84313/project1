#ifndef PAGE3_H
#define PAGE3_H

#include "qpushbutton.h"
#include <QMainWindow>

namespace Ui {
class page3;
}

class page3 : public QMainWindow
{
    Q_OBJECT

public:
    explicit page3(QWidget *parent = nullptr);
    ~page3();

private slots:


    QString loadRandomMap();
    void loadAndProcessMap();

    void onCharacterClicked();
    void onBoardClicked();



private:
    Ui::page3 *ui;
    QVector<QPushButton*> pushButtons;
    QVector<QPushButton*> charactersplayer1;
    QVector<QPushButton*> charactersplayer2;
    //QPushButton* selectedFieldButton = nullptr; // عضوی از کلاس
    //void setupConnections();

    QPushButton* selectedCharacter = nullptr;
    //bool isCharacterSelected = false;
    int player1CharacterCount = 0;
    int player2CharacterCount = 0;
    bool isPlayer1Turn = true;

};

#endif // PAGE3_H
