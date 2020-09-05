#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include "sudoku.h"
#include <ctime>
#include <cstdlib>
#include "position.h"
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);    
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    position *btn_sudoku[81];
    QPushButton *btn_ans;
    QPushButton *btn_select_difficulty;
    QPushButton *btn_complete;
    QPushButton *btn_set_puzzle;
    QPushButton *btn_easy;
    QPushButton *btn_normal;
    QPushButton *btn_hard;
    QPushButton *btn_home;

    QLabel *solution_result;

    void if_vis(Sudoku question,int index);
    bool solve(Sudoku question,Sudoku & answer);
    bool if_legal(Sudoku question);
    bool arr[10]={0};
    Sudoku correct_ans;


private slots:
    void easy_click();
    void hard_click();
    void normal_click();
    void select_difficulty_click();
    void set_puzzle_click();
    void home_click();
    void compelete_click();
    void ans_click();

};


#endif // MAINWINDOW_H
