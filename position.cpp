#include "position.h"
#include <QPushButton>
#include <QDebug>
#include <QMainWindow>

position::position(QWidget *parent):QPushButton(parent)
{
    connect(this,SIGNAL(clicked(bool)),this,SLOT(num_click()));

    //connect(this,SIGNAL(clicked(bool)),this,SLOT())
}
void position::num_click()
{
    //this->setStyleSheet("background:lightblue;");
    qDebug()<<"click "<<this->now;
}

void position::keyPressEvent(QKeyEvent *event)
{
    if(this->judge==false)
    {
        if(event->key()==Qt::Key_1)
        {
            this->setText("1");
            this->num=1;
        }
        if(event->key()==Qt::Key_2)
        {
            this->setText("2");
            this->num=2;
        }
        if(event->key()==Qt::Key_3)
        {
            this->setText("3");
            this->num=3;
        }
        if(event->key()==Qt::Key_4)
        {
            this->setText("4");
            this->num=4;
        }
        if(event->key()==Qt::Key_5)
        {
            this->setText("5");
            this->num=5;
        }
        if(event->key()==Qt::Key_6)
        {
            this->setText("6");
            this->num=6;
        }
        if(event->key()==Qt::Key_7)
        {
            this->setText("7");
            this->num=7;
        }
        if(event->key()==Qt::Key_8)
        {
            this->setText("8");
            this->num=8;
        }
        if(event->key()==Qt::Key_9)
        {
            this->setText("9");
            this->num=9;
        }
        if(event->key()==Qt::Key_Delete)
        {
            this->setText("");
            this->num=0;
        }
    }

}
