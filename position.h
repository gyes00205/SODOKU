#ifndef POSITION_H
#define POSITION_H
#include <QPushButton>
#include <QKeyEvent>

class position:public QPushButton
{
    Q_OBJECT
public:
    position(QWidget *parent);
    int now;
    void keyPressEvent(QKeyEvent *event);
    int num;
    bool judge=0;
public slots:
    void num_click();
};

#endif // POSITION_H
