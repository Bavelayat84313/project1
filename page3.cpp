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
#include <queue>
//#include <queue>
//#include <QPair>




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

    for (int i = 0; i < 41; i++) {
        tilesList[i].button = pushButtons[i];
    }

    // توابعی که باید حتما در اول بازی فراخوانی شوند
    loadRandomMap();
    loadAndProcessMap();

    //onCharacterClicked();
    //onBoardClicked();

    findNeighbors();

    //QList<tiles*> findReachableTiles(tiles* ,int ,int);
    //void highlightReachableTiles(tiles* ,int ,int);
    //resetTileHighlights();

    for (QPushButton* btn : charactersplayer1) {
        connect(btn, &QPushButton::clicked, this, &page3::onCharacterClicked);
    }

    for (QPushButton* btn : charactersplayer2) {
        connect(btn, &QPushButton::clicked, this, &page3::onCharacterClicked);
    }

    for (QPushButton* btn : pushButtons) {
        connect(btn, &QPushButton::clicked, this, [this, btn]() {
            if (gamePhase == PLACEMENT_PHASE) {
                onBoardClicked();
            } else if (selectedCharacterOnBoard) {
                onBoardClicked(); // اگر کاراکتری انتخاب شده، حرکت انجام شود
            } else {
                onCharacterClicked(); // اگر کاراکتری انتخاب نشده، انتخاب انجام شود
            }
        });
    }

    /*for (QPushButton* btn : pushButtons) {
        connect(btn, &QPushButton::clicked, this, &page3::onBoardClicked);
    }*/

    for(QPushButton* btn : charactersplayer2) {
        btn->setEnabled(false);
    }

    ui->label_turn->setText("نوبت بازیکن 1: قرار دادن کاراکترها");
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





    /*int count=0;

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

    }*/


    /*int count = 0;
    for (int j = 0; j < 5; j++) {  // ستون‌ها
        // ردیف‌های زوج برای تمام ستون‌ها
        for (int i = 0; i < 9 && count < 41; i += 2) {
            tilesList[count].row = i;
            tilesList[count].column = j;
            tilesList[count].pic = processedMap[count].digitValue();
            count++;
        }

        // ردیف‌های فرد فقط برای ستون‌های 0 تا 3
        if (j < 4) {
            for (int i = 1; i < 9 && count < 41; i += 2) {
                tilesList[count].row = i;
                tilesList[count].column = j;
                tilesList[count].pic = processedMap[count].digitValue();
                count++;
            }
        }
    }*/


    int count = 0;
    // برای شبکه شش‌ضلعی با 5 ستون و 9 سطر
    for (int col = 0; col < 5; col++) {
        // سطرهای زوج برای تمام ستون‌ها
        for (int row = 0; row < 9 && count < 41; row += 2) {
            tilesList[count].row = row;
            tilesList[count].column = col;
            tilesList[count].pic = processedMap[count].digitValue();
            count++;
        }

        // سطرهای فرد فقط برای ستون‌های 0 تا 3
        if (col < 4) {
            for (int row = 1; row < 9 && count < 41; row += 2) {
                tilesList[count].row = row;
                tilesList[count].column = col;
                tilesList[count].pic = processedMap[count].digitValue();
                count++;
            }
        }
    }


    /*int count = 0;
    // ستون‌های زوج (0, 2, 4) - 5 خانه
    for (int col = 0; col <= 4; col += 2) {
        for (int row = 0; row <= 8 && count < 41; row += 2) {
            tilesList[count].row = row;
            tilesList[count].column = col;
            tilesList[count].pic = processedMap[count].digitValue();
            count++;
        }
    }
    // ستون‌های فرد (1, 3) - 4 خانه
    for (int col = 1; col <= 3; col += 2) {
        for (int row = 1; row <= 7 && count < 41; row += 2) {
            tilesList[count].row = row;
            tilesList[count].column = col;
            tilesList[count].pic = processedMap[count].digitValue();
            count++;
        }
    }*/


    for(int i=0;i<41;i++){
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


tiles* page3::getTileAt(int row, int col) {
    for (int i = 0; i < 41; i++) {
        if (tilesList[i].row == row && tilesList[i].column == col) {
            return &tilesList[i];
        }
    }
    return nullptr;
}


/*void page3::findNeighbors(){

    for (int i = 0; i < 41; i++){
        tiles& current = tilesList[i];
        //current.neighbors.clear(); //تا محاسبات جدید با لیست خالی شروع ‌شود
        current.neighbors.clear();
        current.neighborsDist2.clear();
        current.neighborsDist3.clear();

        int row = current.row;
        int col = current.column;

        // جهت‌های همسایه‌های فاصله 1
        QVector<QPair<int, int>> directionsDist1 = {
            {-1, 0},   // بالا
            {1, 0},    // پایین
            {0, 1},    // راست
            {0, -1},   // چپ
            {-1, 1},   // راست-بالا
            {1, -1}    // چپ-پایین
        };

        // جهت‌های همسایه‌های فاصله 2
        QVector<QPair<int, int>> directionsDist2 = {
            {-2, 0},   // دو خانه بالا
            {2, 0},    // دو خانه پایین
            {0, 2},    // دو خانه راست
            {0, -2},   // دو خانه چپ
            {-2, 1},   //
            {-1, 2},   //
            {1, 1},    //
            {2, -1},   //
            {1, -2},   //
            {-1, -1},  //
            {-2, 2},   //
            {2, -2}    //
        };

        // جهت‌های همسایه‌های فاصله 3
        QVector<QPair<int, int>> directionsDist3 = {
            {-3, 0},   // سه خانه بالا
            {3, 0},    // سه خانه پایین
            {0, 3},    // سه خانه راست
            {0, -3},   // سه خانه چپ
            {-2, 2},   //
            {2, -2},   //
            {-1, 3},   //
            {1, -3},   //
            {-3, 1},   //
            {3, -1},   //
            {-1, -2},  //
            {1, 2},    //
            {-2, -1},  //
            {2, 1},    //
            {-3, 2},   //
            {3, -2},   //
            {-2, 3},   //
            {2, -3}    //
        };

        // یافتن همسایه‌های فاصله 1
        for (const auto& dir : directionsDist1) {
            int newRow = row + dir.first;
            int newCol = col + dir.second;

            if (tiles* neighbor = getTileAt(newRow, newCol)) {
                current.neighbors.append(neighbor);
            }
        }

        // یافتن همسایه‌های فاصله 2
        for (const auto& dir : directionsDist2) {
            int newRow = row + dir.first;
            int newCol = col + dir.second;

            if (tiles* neighbor = getTileAt(newRow, newCol)) {
                current.neighborsDist2.append(neighbor);
            }
        }

        // یافتن همسایه‌های فاصله 3
        for (const auto& dir : directionsDist3) {
            int newRow = row + dir.first;
            int newCol = col + dir.second;

            if (tiles* neighbor = getTileAt(newRow, newCol)) {
                current.neighborsDist3.append(neighbor);
            }
        }
    }
}*/


/*void page3::findNeighbors() {
    for (int i = 0; i < 41; i++) {
        tiles& current = tilesList[i];
        current.neighbors.clear();
        current.neighborsDist2.clear();
        current.neighborsDist3.clear();

        int row = current.row;
        int col = current.column;

        // جهت‌های پایه برای شبکه شش‌ضلعی
        QVector<QPair<int, int>> baseDirections;

        if (col % 2 == 0) {
            // ستون زوج
            baseDirections = {
                {-1, 0},  // بالا
                {1, 0},    // پایین
                {0, 1},    // راست
                {0, -1},   // چپ
                {-1, 1},   // راست-بالا
                {1, 1}     // راست-پایین
            };
        } else {
            // ستون فرد
            baseDirections = {
                {-1, 0},   // بالا
                {1, 0},    // پایین
                {0, 1},    // راست
                {0, -1},   // چپ
                {-1, -1},  // چپ-بالا
                {1, -1}    // چپ-پایین
            };
        }

        // همسایه‌های فاصله 1
        for (const auto& dir : baseDirections) {
            if (tiles* nb = getTileAt(row + dir.first, col + dir.second)) {
                current.neighbors.append(nb);
            }
        }

        // همسایه‌های فاصله 2 (ترکیب دو حرکت فاصله 1)
        QVector<QPair<int, int>> directionsDist2;
        for (const auto& dir1 : baseDirections) {
            for (const auto& dir2 : baseDirections) {
                directionsDist2.append({dir1.first + dir2.first,
                                        dir1.second + dir2.second});
            }
        }

        // حذف موارد تکراری و اضافه کردن
        std::sort(directionsDist2.begin(), directionsDist2.end());
        directionsDist2.erase(std::unique(directionsDist2.begin(),
                                          directionsDist2.end()),
                              directionsDist2.end());

        for (const auto& dir : directionsDist2) {
            if (tiles* nb = getTileAt(row + dir.first, col + dir.second)) {
                current.neighborsDist2.append(nb);
            }
        }

        // همسایه‌های فاصله 3 (ترکیب سه حرکت)
        QVector<QPair<int, int>> directionsDist3;
        for (const auto& dir1 : baseDirections) {
            for (const auto& dir2 : baseDirections) {
                for (const auto& dir3 : baseDirections) {
                    directionsDist3.append({
                        dir1.first + dir2.first + dir3.first,
                        dir1.second + dir2.second + dir3.second
                    });
                }
            }
        }

        // حذف موارد تکراری
        std::sort(directionsDist3.begin(), directionsDist3.end());
        directionsDist3.erase(std::unique(directionsDist3.begin(),
                                          directionsDist3.end()),
                              directionsDist3.end());

        for (const auto& dir : directionsDist3) {
            if (tiles* nb = getTileAt(row + dir.first, col + dir.second)) {
                current.neighborsDist3.append(nb);
            }
        }
    }
}*/


/*void page3::findNeighbors() {
    for (int i = 0; i < 41; i++) {
        tiles& current = tilesList[i];
        current.neighbors.clear();
        current.neighborsDist2.clear();
        current.neighborsDist3.clear();

        int row = current.row;
        int col = current.column;

        // جهت‌های پایه برای شبکه شش‌ضلعی
        QVector<QPair<int, int>> baseDirections;

        if (col % 2 == 0) {
            // ستون زوج
            baseDirections = {
                {-1, 0},  // بالا
                {1, 0},    // پایین
                {0, 1},    // راست
                {0, -1},   // چپ
                {-1, 1},   // راست-بالا
                {1, 1}     // راست-پایین
            };
        } else {
            // ستون فرد
            baseDirections = {
                {-1, 0},   // بالا
                {1, 0},    // پایین
                {0, 1},    // راست
                {0, -1},   // چپ
                {-1, -1},  // چپ-بالا
                {1, -1}    // چپ-پایین
            };
        }

        // همسایه‌های فاصله 1
        for (const auto& dir : baseDirections) {
            if (tiles* nb = getTileAt(row + dir.first, col + dir.second)) {
                current.neighbors.append(nb);
            }
        }

        // استفاده از BFS برای پیدا کردن همسایه‌های فاصله 2 و 3
        QSet<tiles*> visited;
        std::queue<std::pair<tiles*, int>> q;
        q.push({&current, 0});
        visited.insert(&current);

        while (!q.empty()) {
            auto [tile, dist] = q.front();
            q.pop();

            if (dist == 1) {
                current.neighborsDist2.append(tile);
            } else if (dist == 2) {
                current.neighborsDist3.append(tile);
            } else if (dist >= 3) {
                continue;
            }

            for (const auto& dir : baseDirections) {
                int newRow = tile->row + dir.first;
                int newCol = tile->column + dir.second;
                tiles* neighbor = getTileAt(newRow, newCol);
                if (neighbor && !visited.contains(neighbor)) {
                    visited.insert(neighbor);
                    q.push({neighbor, dist + 1});
                }
            }
        }
    }
}*/

/*void page3::findNeighbors() {
    for (int i = 0; i < 41; i++) {
        tiles& current = tilesList[i];
        current.neighbors.clear();

        int row = current.row;
        int col = current.column;

        // جهت‌های همسایه برای شبکه شش‌ضلعی عمودی
        QVector<QPair<int, int>> directions;

        if (row % 2 == 0) {
            // ردیف زوج
            directions = {
                {-1, 0},   // بالا
                {1, 0},    // پایین
                {0, 1},    // راست
                {0, -1},   // چپ
                {-1, -1},  // چپ-بالا
                {1, -1}    // چپ-پایین
            };
        } else {
            // ردیف فرد
            directions = {
                {-1, 0},   // بالا
                {1, 0},    // پایین
                {0, 1},    // راست
                {0, -1},   // چپ
                {-1, 1},   // راست-بالا
                {1, 1}     // راست-پایین
            };
        }

        // همسایه‌های فاصله 1
        for (const auto& dir : directions) {
            if (tiles* nb = getTileAt(row + dir.first, col + dir.second)) {
                current.neighbors.append(nb);
            }
        }
    }
}*/

void page3::findNeighbors() {
    for (int i = 0; i < 41; i++) {
        tiles& current = tilesList[i];
        current.neighbors.clear();

        int row = current.row;
        int col = current.column;

        // جهت‌های همسایه برای شبکه شش‌ضلعی عمودی
        // با توجه به ساختار واقعی شبکه شما
        QVector<QPair<int, int>> directions = {
            {-1, 0},   // بالا
            {1, 0},    // پایین
            {0, 1},    // راست
            {0, -1},   // چپ
        };

        // اضافه کردن جهت‌های مورب بر اساس موقعیت
        if (row % 2 == 0) {
            // ردیف زوج
            directions.append({-1, -1});  // چپ-بالا
            directions.append({1, -1});   // چپ-پایین
        } else {
            // ردیف فرد
            directions.append({-1, 1});   // راست-بالا
            directions.append({1, 1});    // راست-پایین
        }

        // همسایه‌های فاصله 1
        for (const auto& dir : directions) {
            if (tiles* nb = getTileAt(row + dir.first, col + dir.second)) {
                current.neighbors.append(nb);
            }
        }
    }
}

/*QList<tiles*> page3::findReachableTiles(tiles* startTile, int movementRange) {
    QList<tiles*> reachableTiles;

    // ریست وضعیت
    for (int i = 0; i < 41; i++) {
        tilesList[i].visited = false;
        tilesList[i].distance = INT_MAX;
    }

    std::priority_queue<std::pair<int, tiles*>,
                        std::vector<std::pair<int, tiles*>>,
                        std::greater<std::pair<int, tiles*>>> pq;

    startTile->distance = 0;
    pq.push({0, startTile});

    while (!pq.empty()) {
        auto [currentDist, currentTile] = pq.top();
        pq.pop();

        if (currentDist > movementRange) continue;
        if (currentTile->visited) continue;

        currentTile->visited = true;
        reachableTiles.append(currentTile);

        for (tiles* neighbor : currentTile->neighbors) {
            if (!neighbor->visited && neighbor->pic != 4 && neighbor->pic != 5) {
                int newDist = currentDist + 1;
                if (newDist < neighbor->distance) {
                    neighbor->distance = newDist;
                    pq.push({newDist, neighbor});
                }
            }
        }
    }

    return reachableTiles;
}*/

/*QList<tiles*> page3::findReachableTiles(tiles* startTile, int movementRange) {
    QList<tiles*> reachableTiles;

    // ریست وضعیت
    for (int i = 0; i < 41; i++) {
        tilesList[i].visited = false;
        tilesList[i].distance = INT_MAX;
    }

    std::queue<std::pair<tiles*, int>> queue;

    startTile->visited = true;
    startTile->distance = 0;
    queue.push({startTile, 0});
    reachableTiles.append(startTile);

    while (!queue.empty()) {
        auto current = queue.front();
        queue.pop();

        tiles* currentTile = current.first;
        int currentDistance = current.second;

        if (currentDistance >= movementRange) {
            continue;
        }

        for (tiles* neighbor : currentTile->neighbors) {
            if (!neighbor->visited) {
                // خانه‌های آب و کوه کاملاً غیرقابل عبور هستند
                if (neighbor->pic == 4 || neighbor->pic == 5) {
                    continue; // از این همسایه عبور نکن
                }

                neighbor->visited = true;
                neighbor->distance = currentDistance + 1;
                reachableTiles.append(neighbor);
                queue.push({neighbor, currentDistance + 1});
            }
        }
    }

    return reachableTiles;
}*/

/*QList<tiles*> page3::findReachableTiles(tiles* startTile, int movementRange) {
    QList<tiles*> reachableTiles;

    // ریست وضعیت
    for (int i = 0; i < 41; i++) {
        tilesList[i].visited = false;
        tilesList[i].distance = INT_MAX;
    }

    std::queue<std::pair<tiles*, int>> queue;

    startTile->visited = true;
    startTile->distance = 0;
    queue.push({startTile, 0});
    reachableTiles.append(startTile);

    while (!queue.empty()) {
        auto current = queue.front();
        queue.pop();

        tiles* currentTile = current.first;
        int currentDistance = current.second;

        if (currentDistance >= movementRange) {
            continue;
        }

        for (tiles* neighbor : currentTile->neighbors) {
            if (!neighbor->visited) {
                neighbor->visited = true;

                // فقط اگر خانه آب یا کوه نباشد، می‌توان از آن عبور کرد
                if (neighbor->pic != 4 && neighbor->pic != 5) {
                    neighbor->distance = currentDistance + 1;
                    reachableTiles.append(neighbor);
                    queue.push({neighbor, currentDistance + 1});
                } else {
                    // خانه‌های آب و کوه visited می‌شوند اما به آنها distance تعلق نمی‌گیرد
                    neighbor->distance = INT_MAX;
                }
            }
        }
    }

    return reachableTiles;
}*/

QList<tiles*> page3::findReachableTiles(tiles* startTile, int movementRange) {
    QList<tiles*> reachableTiles;

    // ریست وضعیت
    for (int i = 0; i < 41; i++) {
        tilesList[i].visited = false;
        tilesList[i].distance = INT_MAX;
    }

    std::queue<std::pair<tiles*, int>> queue;

    startTile->visited = true;
    startTile->distance = 0;
    queue.push({startTile, 0});

    // همیشه خانه شروع قابل دسترس است (حتی اگر آب یا کوه باشد)
    if (startTile->pic != 4 && startTile->pic != 5) {
        reachableTiles.append(startTile);
    }

    while (!queue.empty()) {
        auto current = queue.front();
        queue.pop();

        tiles* currentTile = current.first;
        int currentDistance = current.second;

        if (currentDistance >= movementRange) {
            continue;
        }

        for (tiles* neighbor : currentTile->neighbors) {
            if (!neighbor->visited) {
                neighbor->visited = true;
                neighbor->distance = currentDistance + 1;

                // خانه را به صف اضافه کن تا مسیرهایش بررسی شود
                queue.push({neighbor, currentDistance + 1});

                // فقط اگر خانه آب یا کوه نباشد، به لیست قابل دسترس اضافه کن
                if (neighbor->pic != 4 && neighbor->pic != 5) {
                    reachableTiles.append(neighbor);
                }
            }
        }
    }

    return reachableTiles;
}

/*void page3::processNeighbor(tiles* neighbor, int currentDist, int step,
                            int maxRange, QList<tiles*>& reachableTiles,
                            std::queue<std::pair<tiles*, int>>& queue) {
    if (!neighbor->visited && currentDist + step <= maxRange) {
        bool canMove = (neighbor->pic != 5 && neighbor->pic != 4); // نه کوه نه آب

        if (canMove) {
            neighbor->visited = true;
            neighbor->distance = currentDist + step;
            reachableTiles.append(neighbor);
            queue.push({neighbor, currentDist + step});
        }
    }
}*/

// bfs برای پیدا کردن تمام کاشی‌های قابل دسترس در محدوده مشخص تابع
/*QList<tiles*> page3::findReachableTiles(tiles* startTile, int movementRange){

    QList<tiles*> reachableTiles;
    std::queue<std::pair<tiles*,int>> queue;

    for (int i = 0; i < 41; i++) {
        tilesList[i].visited = false;
        tilesList[i].distance = INT_MAX;
    }

    startTile->visited = true;
    startTile->distance = 0;
    queue.push({startTile, 0});
    reachableTiles.append(startTile);

    while (!queue.empty()) {

        auto current = queue.front();
        queue.pop();

        tiles* currentTile = current.first;
        int currentDistance = current.second;

        // پردازش همسایه‌های فاصله 1
        for (tiles* neighbor : currentTile->neighbors) {
            processNeighbor(neighbor, currentDistance, 1, movementRange,
                            reachableTiles, queue);
        }

        // پردازش همسایه‌های فاصله 2
        if (movementRange >= 2) {
            for (tiles* neighbor : currentTile->neighborsDist2) {
                processNeighbor(neighbor, currentDistance, 2, movementRange,
                                reachableTiles, queue);
            }
        }

        // پردازش همسایه‌های فاصله 3
        if (movementRange >= 3) {
            for (tiles* neighbor : currentTile->neighborsDist3) {
                processNeighbor(neighbor, currentDistance, 3, movementRange,
                                reachableTiles, queue);
            }
        }
    }
    return reachableTiles;
}*/


/*QList<tiles*> page3::findReachableTiles(tiles* startTile, int movementRange) {
    QList<tiles*> reachableTiles;
    std::queue<std::pair<tiles*, int>> queue;

    // ریست وضعیت
    for (int i = 0; i < 41; i++) {
        tilesList[i].visited = false;
        tilesList[i].distance = INT_MAX;
    }

    startTile->visited = true;
    startTile->distance = 0;
    queue.push({startTile, 0});
    reachableTiles.append(startTile);

    while (!queue.empty()) {
        auto current = queue.front();
        queue.pop();

        tiles* currentTile = current.first;
        int currentDistance = current.second;

        // پردازش همسایه‌ها بر اساس فاصله
        auto processNeighbors = [&](const QList<tiles*>& neighbors, int step) {
            for (tiles* neighbor : neighbors) {
                if (!neighbor->visited &&
                    currentDistance + step <= movementRange &&
                    neighbor->pic != 4 && neighbor->pic != 5) { // نه آب نه کوه

                    neighbor->visited = true;
                    neighbor->distance = currentDistance + step;
                    reachableTiles.append(neighbor);
                    queue.push({neighbor, currentDistance + step});
                }
            }
        };

        processNeighbors(currentTile->neighbors, 1);

        if (movementRange >= 2) {
            processNeighbors(currentTile->neighborsDist2, 2);
        }

        if (movementRange >= 3) {
            processNeighbors(currentTile->neighborsDist3, 3);
        }
    }

    return reachableTiles;
}*/

/*QList<tiles*> page3::findReachableTiles(tiles* startTile, int movementRange) {
    QList<tiles*> reachableTiles;
    std::queue<std::pair<tiles*, int>> queue;

    // ریست وضعیت
    for (int i = 0; i < 41; i++) {
        tilesList[i].visited = false;
        tilesList[i].distance = INT_MAX;
    }

    startTile->visited = true;
    startTile->distance = 0;
    queue.push({startTile, 0});
    reachableTiles.append(startTile);

    while (!queue.empty()) {
        auto current = queue.front();
        queue.pop();

        tiles* currentTile = current.first;
        int currentDistance = current.second;

        if (currentDistance >= movementRange) {
            continue;
        }

        // پردازش همسایه‌ها
        for (tiles* neighbor : currentTile->neighbors) {
            if (!neighbor->visited && neighbor->pic != 4 && neighbor->pic != 5) {
                neighbor->visited = true;
                neighbor->distance = currentDistance + 1;
                reachableTiles.append(neighbor);
                queue.push({neighbor, currentDistance + 1});
            }
        }
    }

    return reachableTiles;
}*/

/*void page3::highlightReachableTiles(tiles* startTile, int movementRange){

    resetTileHighlights();  // ابتدا همه هایلایت‌ها را پاک کنید

    QList<tiles*> reachable = findReachableTiles(startTile, movementRange); //کاشی‌های قابل دسترس را پیدا کنید

    debugReachableTiles(startTile, movementRange);

    for (tiles* tile : reachable){
        if (tile != startTile){
            QString color;
            if (tile->distance == 1) color = "lightgreen";
            else if (tile->distance == 2) color = "green";
            else if (tile->distance == 3) color = "red";
            tile->button->setStyleSheet(
                QString("background-color: %1; border: 2px solid yellow;").arg(color));
        }
    }
}*/

/*void page3::highlightReachableTiles(tiles* startTile, int movementRange){
    resetTileHighlights();
    QList<tiles*> reachable = findReachableTiles(startTile, movementRange);

    debugReachableTiles(startTile, movementRange);

    for (tiles* tile : reachable){
        if (tile != startTile){
            QString color;
            if (tile->distance <= 1) color = "lightgreen";
            else if (tile->distance <= 2) color = "green";
            else if (tile->distance <= 3) color = "red";

            tile->button->setStyleSheet(
                QString("background-color: %1; border: 2px solid yellow;").arg(color));
        }
    }
}*/

void page3::highlightReachableTiles(tiles* startTile, int movementRange){
    resetTileHighlights();
    QList<tiles*> reachable = findReachableTiles(startTile, movementRange);

    debugReachableTiles(startTile, movementRange);

    for (tiles* tile : reachable){
        if (tile != startTile && tile->distance <= movementRange){
            QString color;
            if (tile->distance == 1) color = "lightgreen";
            else if (tile->distance == 2) color = "green";
            else if (tile->distance == 3) color = "red";

            tile->button->setStyleSheet(
                QString("background-color: %1; border: 2px solid yellow;").arg(color));
        }
    }
}

void page3::resetTileHighlights(){

    for (int i = 0; i < 41; i++){
         tiles& tile = tilesList[i];

        if (tile.pic == 1) {
            tile.button->setStyleSheet("background-color: cyan;");
        }
        else if (tile.pic == 2) {
            tile.button->setStyleSheet("background-color: pink;");
        }
        else if (tile.pic == 3) {
            tile.button->setStyleSheet("background-color: yellow;");
        }
        else if (tile.pic == 4) {
            tile.button->setStyleSheet("background-color: blue;");
        }
        else if (tile.pic == 5) {
            tile.button->setStyleSheet("background-color: brown;");
        }
    }
}


void page3::onCharacterClicked() {

    QPushButton* clickedBtn = qobject_cast<QPushButton*>(sender());
    if (!clickedBtn) return;

    if (gamePhase == PLACEMENT_PHASE) {

        selectedCharacterFromPanel = clickedBtn;
        clickedBtn->setStyleSheet("background-color: yellow;");
    }

    else if (gamePhase == MOVEMENT_PHASE) {

        // پیدا کردن کاشی مربوطه
        for (int i = 0; i < 41; i++) {
            if (tilesList[i].button == clickedBtn) {
                // ریست انتخاب قبلی
                if (selectedCharacterOnBoard) {
                    selectedCharacterOnBoard->setStyleSheet("");
                }
                selectedCharacterOnBoard = tilesList[i].button; // استفاده از دکمه زمین از tilesList
                selectedCharacterOnBoard->setStyleSheet("border: 3px solid yellow;");

                int movementRange = 3;
                highlightReachableTiles(&tilesList[i], movementRange);
                break;
            }
        }
    }
}

/*void page3::onCharacterClicked() {
    QPushButton* clickedBtn = qobject_cast<QPushButton*>(sender());
    if (!clickedBtn) return;

    // فقط برای فاز حرکت
    if (gamePhase != MOVEMENT_PHASE) return;

    // پیدا کردن کاشی مربوطه
    for (int i = 0; i < 41; i++) {
        if (tilesList[i].button == clickedBtn) {
            // ریست انتخاب قبلی
            if (selectedCharacterOnBoard) {
                selectedCharacterOnBoard->setStyleSheet("");
            }

            selectedCharacterOnBoard = tilesList[i].button;
            selectedCharacterOnBoard->setStyleSheet("border: 3px solid yellow;");

            int movementRange = 3;
            highlightReachableTiles(&tilesList[i], movementRange);

            qDebug() << "Character selected:" << selectedCharacterOnBoard; // برای دیباگ
            return;
        }
    }

    qDebug() << "Clicked button not found in tilesList!"; // برای دیباگ
}*/

void page3::onBoardClicked() {

    QPushButton* targetBtn = qobject_cast<QPushButton*>(sender());
    if (!targetBtn) return;

    int tileIndex = pushButtons.indexOf(targetBtn);
    if (tileIndex == -1) return;

    if (gamePhase == PLACEMENT_PHASE){

        if (isPlayer1Turn){

            if (tilesList[tileIndex].pic != 1) {
                QMessageBox::warning(this, "خطا", "بازیکن ۱ فقط می‌تواند در زمین‌های آبی کاراکتر قرار دهد!");
                return;
            }

            // قرار دادن کاراکتر روی زمین
            targetBtn->setIcon(selectedCharacterFromPanel->icon());
            selectedCharacterFromPanel->setIcon(QIcon());
            selectedCharacterFromPanel->setStyleSheet("");

            player1CharacterCount++;

            player1CharactersOnBoard.append(targetBtn);

            if (player1CharacterCount >= 5) {

                for(QPushButton* btn : charactersplayer1) {
                    btn->setEnabled(false);
                }

                for(QPushButton* btn : charactersplayer2) {
                    btn->setEnabled(true);
                }

                isPlayer1Turn = false;
                ui->label_turn->setText("نوبت بازیکن 2: قرار دادن کاراکترها");
            }
        }

        else {

            if (tilesList[tileIndex].pic != 2) {
                QMessageBox::warning(this, "خطا", "بازیکن ۲ فقط می‌تواند در زمین‌های صورتی کاراکتر قرار دهد!");
                return;
            }

            // قرار دادن کاراکتر روی زمین
            targetBtn->setIcon(selectedCharacterFromPanel->icon());
            selectedCharacterFromPanel->setIcon(QIcon());
            selectedCharacterFromPanel->setStyleSheet("");

            player2CharacterCount++;

            player2CharactersOnBoard.append(targetBtn);

            if (player2CharacterCount >= 5) {

                for(QPushButton* btn : charactersplayer2) {
                    btn->setEnabled(false);
                }

                // تغییر به فاز حرکت
                gamePhase = MOVEMENT_PHASE;
                isPlayer1Turn = true;
                ui->label_turn->setText("نوبت بازیکن 1: حرکت کاراکترها");
            }
        }
    }

    else if (gamePhase == MOVEMENT_PHASE){

        if (!selectedCharacterOnBoard) {
            QMessageBox::warning(this, "خطا", "لطفاً ابتدا یک کاراکتر از زمین انتخاب کنید!");
            return;
        }

        // بررسی تعلق کاراکتر به بازیکن فعلی
        bool belongsToCurrentPlayer = false;

        tiles* sourceTile = nullptr;
        for (int i = 0; i < 41; i++) {
            if (tilesList[i].button == selectedCharacterOnBoard) {
                sourceTile = &tilesList[i];
                if (isPlayer1Turn) {
                    belongsToCurrentPlayer = player1CharactersOnBoard.contains(tilesList[i].button);
                }
                else {
                    belongsToCurrentPlayer = player2CharactersOnBoard.contains(tilesList[i].button);
                }
                break;
            }
        }

        if (!belongsToCurrentPlayer) {
            QMessageBox::warning(this, "خطا", "شما فقط می‌توانید کاراکترهای خود را حرکت دهید!");
            return;
        }

        if (!sourceTile) {
            QMessageBox::warning(this, "خطا", "کاراکتر انتخابی معتبر نیست!");
            return;
        }

        // بررسی اینکه آیا کاشی هدف قابل دسترس است
        QList<tiles*> reachable = findReachableTiles(sourceTile, 3);
        bool isReachable = false;
        for (tiles* tile : reachable) {
            if (tile == &tilesList[tileIndex]) {
                isReachable = true;
                break;
            }
        }
        if (!isReachable || tilesList[tileIndex].pic == 4 || tilesList[tileIndex].pic == 5) {
            QMessageBox::warning(this, "خطا", "این حرکت مجاز نیست!");
            return;
        }


        // انجام حرکت
        targetBtn->setIcon(selectedCharacterOnBoard->icon());
        sourceTile->button->setIcon(QIcon());

        //  بروزرسانی لیست کاراکترهای بازیکن ها
        if (isPlayer1Turn) {
            player1CharactersOnBoard.removeOne(sourceTile->button);
            player1CharactersOnBoard.append(targetBtn);
        } else {
            player2CharactersOnBoard.removeOne(sourceTile->button);
            player2CharactersOnBoard.append(targetBtn);
        }

        selectedCharacterOnBoard->setStyleSheet("");
        selectedCharacterOnBoard = nullptr;
        resetTileHighlights();

        // تغییر نوبت
        isPlayer1Turn = !isPlayer1Turn;
        if (isPlayer1Turn) {
            ui->label_turn->setText("نوبت بازیکن 1: حرکت کاراکترها");
        }
        else {
            ui->label_turn->setText("نوبت بازیکن 2: حرکت کاراکترها");
        }
    }
}

/*void page3::debugTilePositions() {
    qDebug() << "Tile Positions:";
    for (int i = 0; i < 41; i++) {
        qDebug() << "Tile" << i << ": row =" << tilesList[i].row
                 << ", col =" << tilesList[i].column
                 << ", type =" << tilesList[i].pic;
    }

    // بررسی همسایه‌های یک کاشی مرکزی
    int centerIndex = 2; // مثال: کاشی مرکزی
    qDebug() << "Neighbors of tile" << centerIndex << ":";
    for (tiles* neighbor : tilesList[centerIndex].neighbors) {
        int idx = neighbor - tilesList; // محاسبه اندیس
        qDebug() << " - Tile" << idx << ": row =" << neighbor->row
                 << ", col =" << neighbor->column;
    }
}*/

void page3::debugReachableTiles(tiles* startTile, int movementRange) {
    qDebug() << "=== DEBUG REACHABLE TILES ===";
    qDebug() << "Start tile:" << startTile - tilesList << "(row:" << startTile->row << ", col:" << startTile->column << ")";
    qDebug() << "Movement range:" << movementRange;

    // ریست وضعیت
    for (int i = 0; i < 41; i++) {
        tilesList[i].visited = false;
        tilesList[i].distance = INT_MAX;
    }

    std::queue<std::pair<tiles*, int>> queue;

    startTile->visited = true;
    startTile->distance = 0;
    queue.push({startTile, 0});

    qDebug() << "\nBFS traversal (including water/mountains in path):";

    while (!queue.empty()) {
        auto current = queue.front();
        queue.pop();

        tiles* currentTile = current.first;
        int currentDistance = current.second;

        qDebug() << "  Tile" << currentTile - tilesList << "- Distance:" << currentDistance
                 << "- Type:" << currentTile->pic;

        if (currentDistance >= movementRange) {
            continue;
        }

        for (tiles* neighbor : currentTile->neighbors) {
            if (!neighbor->visited) {
                neighbor->visited = true;
                neighbor->distance = currentDistance + 1;
                queue.push({neighbor, currentDistance + 1});

                QString typeStr;
                if (neighbor->pic == 4) typeStr = "WATER";
                else if (neighbor->pic == 5) typeStr = "MOUNTAIN";
                else typeStr = "NORMAL";

                qDebug() << "    -> Neighbor" << neighbor - tilesList << "- Dist:" << currentDistance + 1
                         << "- Type:" << typeStr;
            }
        }
    }

    qDebug() << "\nFinal reachable tiles (non-water/non-mountain):";
    for (int i = 0; i < 41; i++) {
        if (tilesList[i].distance <= movementRange &&
            tilesList[i].distance != INT_MAX &&
            tilesList[i].pic != 4 &&
            tilesList[i].pic != 5) {
            qDebug() << "  Tile" << i << "- Distance:" << tilesList[i].distance;
        }
    }
    qDebug() << "=== END DEBUG ===";
}
