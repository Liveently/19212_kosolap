#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE


class Widget : public QWidget
{
    Q_OBJECT

public:
    int map[10][10];

    Widget(QWidget *parent = nullptr);
    ~Widget();
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void next_move();

private slots:

    void on_restart_clicked();
    void on_menu_clicked();
    void on_start_clicked();
    void on_exit_clicked();

private:
    Ui::Widget *ui;
    QPixmap player;
    QPixmap wall;
    QPixmap ball;
    QPixmap basket;
    QPixmap empty;
    QPixmap goal;
    int game_page = 1;
    int no_map;

    int MyMap[3][10][10]  //1 игрок;2 стена;3 мяч;4 корзина;5 пусто; 
    {
           {{2,2,2,2,2,2,2,2,2,2},
            {2,4,5,5,5,5,5,5,4,2},
            {2,2,2,2,5,5,2,2,2,2},
            {2,5,5,5,5,5,5,5,5,2},
            {2,5,3,5,5,5,5,3,5,2},
            {2,5,3,5,1,5,5,3,5,2},
            {2,5,5,5,5,5,5,5,5,2},
            {2,2,2,2,5,5,2,2,2,2},
            {2,4,5,5,5,5,5,5,4,2},
            {2,2,2,2,2,2,2,2,2,2}},// map 1

        
           {{2,2,2,2,2,2,2,2,2,2},
            {2,5,5,2,5,5,5,5,4,2},
            {2,5,3,2,3,2,2,5,5,2},
            {2,5,5,5,5,5,5,5,5,2},
            {2,2,5,2,5,5,5,2,5,2},
            {2,5,5,1,5,5,3,5,5,2},
            {2,5,5,2,2,5,5,2,4,2},
            {2,5,5,5,2,5,2,2,5,2},
            {2,4,5,5,5,5,5,5,5,2},
            {2,2,2,2,2,2,2,2,2,2}},// map 2

        
           {{2,2,2,2,2,2,2,2,2,2},
            {2,5,5,5,5,5,4,5,5,2},
            {2,5,5,5,5,2,2,4,5,2},
            {2,2,2,5,5,2,4,5,5,2},
            {2,4,2,3,3,2,5,5,5,2},
            {2,5,3,5,1,3,5,5,5,2},
            {2,5,2,3,3,2,5,5,2,2},
            {2,5,5,5,5,5,5,5,4,2},
            {2,4,5,5,5,5,5,2,2,2},
            {2,2,2,2,2,2,2,2,2,2}}//map 3     
    };
};

#endif // WIDGET_H


