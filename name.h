#ifndef NAME_H
#define NAME_H

#include <QMainWindow>

namespace Ui {
class name;
}

class name : public QMainWindow
{
    Q_OBJECT

public:
    explicit name(QWidget *parent = nullptr);
    ~name();

private slots:
    void on_pushButton_clicked();

private:
    Ui::name *ui;
};

#endif // NAME_H
