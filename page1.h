#ifndef PAGE1_H
#define PAGE1_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class page1;
}
QT_END_NAMESPACE

class page1 : public QMainWindow
{
    Q_OBJECT

public:
    page1(QWidget *parent = nullptr);
    ~page1();



private slots:
    void on_pushButton_clicked();

private:
    Ui::page1 *ui;
};
#endif // PAGE1_H
