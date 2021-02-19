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
    void on_load_clicked();

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
    int count=3;

    std::vector<std::vector<std::vector<int>>> MyMap;
};

#endif // WIDGET_H

