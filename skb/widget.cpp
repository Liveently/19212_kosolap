#include "widget.h"
#include "ui_widget.h"
#include <QPaintEvent>
#include <QPainter>
#include <QFileDialog>
#include <QTextStream>
#include <QErrorMessage>


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

    ui->stackedWidget->setCurrentWidget(ui->page_hello);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    if(game_page==1) return;

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

void Widget::keyPressEvent(QKeyEvent *event)
{

   int my_key = event->key();

   int i=0,j=0;

   for (i=0; i<10; ++i) //положение игрока
    {
        for (j=0; j<10;++j)
            if (map[i][j]==1) break;

        if (map[i][j]==1) break;
    }

    switch(my_key)
    {
    case Qt::Key_W:
        if (map[i][j-1]==5)
        {
            map[i][j]=5;
            map[i][j-1]=1;
        } // если идём вперёд и впереди пустое место
        else if (map[i][j-1]==3 && map[i][j-2]==5)
        {
            map[i][j]=5;
            map[i][j-1]=1;
            map[i][j-2]=3;
        } // если впереди мяч, а за ним пусто
        else if (map[i][j-1]==3 && map[i][j-2]==4)
        {
            map[i][j]=5;
            map[i][j-1]=1;
            map[i][j-2]=6;
        }// если впереди мяч, а за ним корзина
        break;
    case Qt::Key_S:
        if (map[i][j+1]==5)
        {
            map[i][j]=5;
            map[i][j+1]=1;
        }
        else if (map[i][j+1]==3 && map[i][j+2]==5)
        {
            map[i][j] = 5;
            map[i][j+1]=1;
            map[i][j+2]=3;
        }
        else if (map[i][j+1]==3 && map[i][j+2]==4)
        {
            map[i][j]=5;
            map[i][j+1]=1;
            map[i][j+2]=6;
        }
        break;
    case Qt::Key_D:
        if (map[i+1][j]==5)
        {
            map[i][j]=5;
            map[i+1][j]=1;
        }
        else if (map[i+1][j]==3 && map[i+2][j]==5)
        {
            map[i][j]=5;
            map[i+1][j]=1;
            map[i+2][j]=3;
        }
        else if (map[i+1][j]==3 && map[i+2][j]==4)
        {
            map[i][j]=5;
            map[i+1][j]=1;
            map[i+2][j]=6;
        }
        break;
    case Qt::Key_A:
        if (map[i-1][j]==5)
        {
            map[i][j]=5;
            map[i-1][j]=1;
        }
        else if (map[i-1][j]==3 && map[i-2][j]==5)
        {
            map[i][j]=5;
            map[i-1][j]=1;
            map[i-2][j]=3;
        }
        else if (map[i-1][j]==3 && map[i-2][j]==4)
        {
            map[i][j]=5;
            map[i-1][j]=1;
            map[i-2][j]=6;
        }
        break;
    }

    update();
    next_move();
}

void Widget::next_move()
{
    for(int i=0;i<10;++i)
        for(int j=0;j<10;++j)
            if (map[i][j]==4) return; // если есть пустые корзины, то продолжаем игру

    ui->stackedWidget->setCurrentWidget(ui->page_hello); //при победе загружается меню
    game_page=1;
}

void Widget::on_restart_clicked()
{
    for(int i=0;i<10;++i)
        for(int j=0;j<10;++j)
              map[i][j] = MyMap[no_map-1][i][j];

    update();
}

void Widget::on_menu_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_hello);
    game_page=1;
}

void Widget::on_start_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_game);
    game_page = 2;

    QString str = ui->comboBox->currentText();
    no_map = str.toInt();

    for(int i=0;i<10;++i)
        for(int j=0;j<10;++j)
            map[i][j] = MyMap[no_map-1][i][j];
}

void Widget::on_exit_clicked()
{
        close();
}


void Widget::on_load_clicked()
{

    QString filename = QFileDialog :: getOpenFileName( this, "Add map", "C:/Users/Luna/Desktop", "Text Files(*.txt)");

    if(filename.length()<1){
        (new QErrorMessage(this))->showMessage("Ошибка загрузки карты");
        return;
    }

    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly)){
        (new QErrorMessage(this))->showMessage("Ошибка загрузки карты");
        return;
    }

    QTextStream stream(&file);

    QString str=stream.readAll();

    file.close();


    if(str.length()!=100){
        (new QErrorMessage(this))->showMessage("Это не карта! Карта должна быть 10*10");
        return;
    }


    int k=0;
    int count1=0;
    int count_ball=0;

    for(int i=0;i<10;++i)
        for(int j=0;j<10;++j){
            if (str[k]=='1')
            {
                MyMap[count][i][j]=1;
                count1++;
            }
            else if (str[k]=='2') MyMap[count][i][j]=2;
            else if (str[k]=='3')
            {
                MyMap[count][i][j]=3;
                count_ball++;
            }
            else if (str[k]=='4')
            {
                MyMap[count][i][j]=4;
                count_ball--;
            }
            else if (str[k]=='5') MyMap[count][i][j]=5;
            else {
                (new QErrorMessage(this))->showMessage("Это не карта! Содержится неизвестный символ");
                return;
            }
            k++;
        }

    if(count1!=1 || count_ball!=0){
        (new QErrorMessage(this))->showMessage("Некорректная карта! Должен быть 1 игрок и одинаковое колличество мячей и корзин");
        return;
    }

    count++;
    QString name = QString::number(count);
    ui->comboBox->addItem(name, count-1);
}

