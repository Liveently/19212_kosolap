#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mymap.h"



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
    void KeyManipuation(int UserKey);
    void loadmap(int m);
    bool GameOver();
    void Winning();

private slots:
    void on_pdb_start_clicked();

    void on_pdb_exit_clicked();

private:
    Ui::Widget *ui;
    QPixmap player;
    QPixmap wall;
    QPixmap ball;
    QPixmap basket;
    QPixmap empty;
    QPixmap goal;
    int game_page = 1;
};
#endif // WIDGET_H
