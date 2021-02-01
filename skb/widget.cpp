
#include "widget.h"
#include "ui_widget.h"
#include "mymap.h"
#include <QPixmap>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    player.load("C:/Users/Luna/Desktop/lab2/pic/1.jpg");
    wall.load("C:/Users/Luna/Desktop/lab2/pic/2.jpg");
    ball.load("C:/Users/Luna/Desktop/lab2/pic/3.jpg");
    basket.load("C:/Users/Luna/Desktop/lab2/pic/4.jpg");
    empty.load("C:/Users/Luna/Desktop/lab2/pic/5.jpg");
    goal.load("C:/Users/Luna/Desktop/lab2/pic/6.jpg");

    ui->stackedWidget->setCurrentWidget(ui->page_welcomr);
    update();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    if(game_page==1) //страница меню
    {
        QPainter p;
        p.begin(this);
        p.end();
    }
    if(game_page==2) //страница уровня
    {

        for(int i=0;i<600;++i)
        {
            for(int j=0;j<600;++j)
             {
                QPainter p;
                p.begin(this);
                switch (map[i][j])
                {
                case 1: p.drawPixmap(i*60,j*60,60,60,player); break;
                case 2: p.drawPixmap(i*60,j*60,60,60,wall); break;
                case 3: p.drawPixmap(i*60,j*60,60,60,ball); break;
                case 4: p.drawPixmap(i*60,j*60,60,60,basket); break;
                case 5: p.drawPixmap(i*60,j*60,60,60,empty); break;
                case 6: p.drawPixmap(i*60,j*60,60,60,goal); break;
                }
                p.end();
            }
        }
    }
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if(event->key()!=Qt::Key_A&&event->key()!=Qt::Key_S&&event->key()!=Qt::Key_D&&event->key()!=Qt::Key_W)
        return;
    int mykey = event->key();
    KeyManipuation(mykey);
} // нажатие кнопки

void Widget::KeyManipuation(int UserKey) //ход
{
    if(game_page==1)
        return;
    int i=0,j=0;

   for (i = 0; i < 10; ++i) //положение игрока
    {
        for (j = 0; j < 10; ++j)
        {
            if (map[i][j] == 1) break;
        }
        if (map[i][j] == 1 ) break;
    }


    switch(UserKey)
    {
    case Qt::Key_W:
        if (map[i][j - 1] == 5)
        {
            map[i][j] = 5;
            map[i][j - 1] = 1;
        } // если идём вперёд и впереди пустое место
        else if (map[i][j - 1] == 3 && map[i][j - 2] == 5)
        {
            map[i][j] = 5;
            map[i][j - 1] = 1;
            map[i][j - 2] = 3;
        } // если впереди мяч, а за ним пусто
        else if (map[i][j - 1] == 3 && map[i][j - 2] == 4)
        {
            map[i][j] = 5;
            map[i][j - 1] = 1;
            map[i][j - 2] = 6;
        }// если впереди мяч, а за ним корзина
        break;
    case Qt::Key_S:
        if (map[i][j + 1] == 5)
        {
            map[i][j] = 5;
            map[i][j + 1] = 1;
        }
        else if (map[i][j + 1] == 3 && map[i][j + 2] == 5)
        {
            map[i][j] = 5;
            map[i][j + 1] = 1;
            map[i][j + 2] = 3;
        }
        else if (map[i][j + 1] == 3 && map[i][j + 2] == 4)
        {
            map[i][j] = 5;
            map[i][j + 1] = 1;
            map[i][j + 2] = 6;
        }
        break;
    case Qt::Key_D:
        if (map[i + 1][j] == 5)
        {
            map[i][j] = 5;
            map[i + 1][j] = 1;
        }
        else if (map[i + 1][j] == 3 && map[i + 2][j] == 5)
        {
            map[i][j] = 5;
            map[i + 1][j] = 1;
            map[i + 2][j] = 3;
        }
        else if (map[i + 1][j] == 3 && map[i + 2][j] == 4)
        {
            map[i][j] = 5;
            map[i + 1][j] = 1;
            map[i + 2][j] = 6;
        }
        break;
    case Qt::Key_A:
        if (map[i - 1][j] == 5)
        {
            map[i][j] = 5;
            map[i - 1][j] = 1;
        }
        else if (map[i - 1][j] == 3 && map[i - 2][j] == 5)
        {
            map[i][j] = 5;
            map[i - 1][j] = 1;
            map[i - 2][j] = 3;
        }
        else if (map[i - 1][j] == 3 && map[i - 2][j] == 4)
        {
            map[i][j] = 5;
            map[i - 1][j] = 1;
            map[i - 2][j] = 6;
        }
        break;

    }

    update();
    if(GameOver())
        Winning();
}

bool Widget::GameOver()
{
    for(int i=0;i<10;++i)
        for(int j=0;j<10;++j)
            if(map[i][j]==3)
                return false;
    return true;
} //конец игры, если на поле нет мячей

void Widget::Winning()
{
    ui->stackedWidget->setCurrentWidget(ui->page_welcomr);
    game_page=1;
} //при победе загружается меню


void Widget::on_pdb_start_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_game);
    game_page = 2;

    QString str = ui->comboBox->currentText();
    int m = str.toInt();
    loadmap(m);
} //кнопка старта


void Widget::on_pdb_exit_clicked()
{
    close();
} // кнопка выход


void Widget::loadmap(int m)
{
    MyMap mp;
    if(m>3)
        return;
    for(int i=0;i<10;++i)
        for(int j=0;j<10;++j)
            map[i][j] = mp.THEmap[m-1][i][j];
} //загружаем карту
