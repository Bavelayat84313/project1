#ifndef PAGE3_H
#define PAGE3_H

#include "qpushbutton.h"
#include <QMainWindow>
#include "tiles.h"
#include <queue>

enum GamePhase {
    PLACEMENT_PHASE, // فاز قرار دادن کاراکترها
    MOVEMENT_PHASE   // فاز حرکت دادن کاراکترها
};

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

    tiles* getTileAt(int, int);
    void findNeighbors();
    //void processNeighbor(tiles*, int, int, int, QList<tiles*>&, std::queue<std::pair<tiles*, int>>&);
    QList<tiles*> findReachableTiles(tiles*, int);
    void highlightReachableTiles(tiles*, int);
    void resetTileHighlights();
    //void debugTilePositions();
    void debugReachableTiles(tiles*, int);


private:
    Ui::page3 *ui;
    QVector<QPushButton*> pushButtons;
    QVector<QPushButton*> charactersplayer1;
    QVector<QPushButton*> charactersplayer2;
    //QPushButton* selectedFieldButton = nullptr; // عضوی از کلاس
    //void setupConnections();

    QPushButton* selectedCharacterFromPanel = nullptr; // برای فاز قرارگیری
    QPushButton* selectedCharacterOnBoard = nullptr;   // برای فاز حرکت
    //QPushButton* selectedCharacter = nullptr;
    //bool isCharacterSelected = false;

    GamePhase gamePhase = PLACEMENT_PHASE;
    bool isPlayer1Turn = true;
    int player1CharacterCount = 0;
    int player2CharacterCount = 0;

    QVector<QPushButton*> player1CharactersOnBoard;
    QVector<QPushButton*> player2CharactersOnBoard;
};

#endif // PAGE3_H
