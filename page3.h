#ifndef PAGE3_H
#define PAGE3_H

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

    void on_pushButton_3_clicked();

private:
    Ui::page3 *ui;
};

#endif // PAGE3_H
