#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sudoku.h"
#include <ctime>
#include <cstdlib>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Sudoku"));

    //sudoku
    int j=0;
    for(int i=0;i<81;i++)
    {
        if(i%9==0) j++;
        btn_sudoku[i] = new position(this);
        btn_sudoku[i]->setGeometry(30+40*(i%9),40*j,40,40);
        btn_sudoku[i]->setText("");
        btn_sudoku[i]->setStyleSheet("background:white;font-size:20px");
        btn_sudoku[i]->now=i;
        btn_sudoku[i]->num=0;
    }
    for(int i=3;i<=5;++i)
        for(int j=0;j<=18;j+=9)
            btn_sudoku[i+j]->setStyleSheet("background:gray;font-size:20px");

    for(int i=27;i<=29;++i)
        for(int j=0;j<=18;j+=9)
            btn_sudoku[i+j]->setStyleSheet("background:gray;font-size:20px");

    for(int i=33;i<=35;++i)
        for(int j=0;j<=18;j+=9)
            btn_sudoku[i+j]->setStyleSheet("background:gray;font-size:20px");

    for(int i=57;i<=59;++i)
        for(int j=0;j<=18;j+=9)
            btn_sudoku[i+j]->setStyleSheet("background:gray;font-size:20px");

    solution_result = new QLabel(this);
    solution_result->setText("Label");
    solution_result->setGeometry(30,400,320,50);
    solution_result->setStyleSheet("font-size:40px;");
    solution_result->setAlignment(Qt::AlignCenter);
    solution_result->hide();

    //Home
    btn_home = new QPushButton(this);
    btn_home->setGeometry(420,20,100,30);
    btn_home->setText("Home");
    btn_home->show();

    //Complete
    btn_complete = new QPushButton(this);
    btn_complete->setGeometry(420,370,100,30);
    btn_complete->setText("Complete!!");
    btn_complete->hide();

    //set puzzle
    btn_set_puzzle = new QPushButton(this);
    btn_set_puzzle->setGeometry(420,320,100,30);
    btn_set_puzzle->setText("set puzzle");

    //select difficulty
    btn_select_difficulty = new QPushButton(this);
    btn_select_difficulty->setGeometry(420,270,100,30);
    btn_select_difficulty->setText("Difficulty");

    //Hard
    btn_hard = new QPushButton(this);
    btn_hard->setGeometry(420,220,100,30);
    btn_hard->setText("Hard");
    btn_hard->hide();

    //Normal
    btn_normal = new QPushButton(this);
    btn_normal->setGeometry(420,170,100,30);
    btn_normal->setText("Normal");
    btn_normal->hide();

    //Easy
    btn_easy = new QPushButton(this);
    btn_easy->setGeometry(420,120,100,30);
    btn_easy->setText("Easy");
    btn_easy->hide();

    //Generate
    btn_ans = new QPushButton(this);
    btn_ans->setGeometry(420,70,100,30);
    btn_ans->setText("Answer");
    btn_ans->hide();

    //click select difficulty
    connect(btn_select_difficulty,SIGNAL(clicked(bool)),this,SLOT(select_difficulty_click()));

    //click set puzzle
    connect(btn_set_puzzle,SIGNAL(clicked(bool)),this,SLOT(set_puzzle_click()));

    //click Easy
    connect(btn_easy,SIGNAL(clicked(bool)),this,SLOT(easy_click()));

    //click Normal
    connect(btn_normal,SIGNAL(clicked(bool)),this,SLOT(normal_click()));

    //click Hard
    connect(btn_hard,SIGNAL(clicked(bool)),this,SLOT(hard_click()));

    //click Home
    connect(btn_home,SIGNAL(clicked(bool)),this,SLOT(home_click()));

    //click Compelete
    connect(btn_complete,SIGNAL(clicked(bool)),this,SLOT(compelete_click()));

    //click Answer
    connect(btn_ans,SIGNAL(clicked(bool)),this,SLOT(ans_click()));
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::select_difficulty_click()
{
    btn_easy->show();
    btn_hard->show();
    btn_normal->show();
    btn_select_difficulty->hide();
    btn_set_puzzle->hide();
}

void MainWindow::set_puzzle_click()
{
    btn_select_difficulty->hide();
    btn_set_puzzle->hide();
    Sudoku ques;
    Sudoku ans;
    for(int i=0;i<81;i++)
    {
        ques.setElement(i,btn_sudoku[i]->num);
    }
    for(int i=0;i<81;++i)
    {
        if(ques.getElement(i)==0)
            btn_sudoku[i]->setText("");
        else
        {
            btn_sudoku[i]->setText(QString::number(ques.getElement(i)));
            btn_sudoku[i]->setStyleSheet("background:yellow;font-size:20px");
            btn_sudoku[i]->judge=1;
        }

    }
    if(if_legal(ques))
    {
        if(solve(ques,ans)==true)
        {
            correct_ans=ans;
            btn_complete->show();
            btn_ans->show();
            solution_result->show();
            solution_result->setText("Solvable!!");
            solution_result->setStyleSheet("color:green;font-size:40px;");
        }
        else
        {
            solution_result->show();
            solution_result->setText("Unsolvable!!");
            solution_result->setStyleSheet("color:red;font-size:40px;");
        }
    }
    else
    {
        solution_result->show();
        solution_result->setText("Unsolvable!!");
        solution_result->setStyleSheet("color:red;font-size:40px;");
    }
}

void MainWindow::home_click()
{
    for(int i=0;i<81;i++)
    {
        btn_sudoku[i]->setText("");
        btn_sudoku[i]->setStyleSheet("background:white;font-size:20px");
    }
    btn_complete->hide();
    btn_set_puzzle->show();
    btn_select_difficulty->show();
    btn_easy->hide();
    btn_normal->hide();
    btn_hard->hide();
    solution_result->hide();
    btn_ans->hide();
    for(int i=0;i<81;++i)
    {
        btn_sudoku[i]->num=0;
        btn_sudoku[i]->judge=0;
    }
    for(int i=3;i<=5;++i)
        for(int j=0;j<=18;j+=9)
            btn_sudoku[i+j]->setStyleSheet("background:gray;font-size:20px");

    for(int i=27;i<=29;++i)
        for(int j=0;j<=18;j+=9)
            btn_sudoku[i+j]->setStyleSheet("background:gray;font-size:20px");

    for(int i=33;i<=35;++i)
        for(int j=0;j<=18;j+=9)
            btn_sudoku[i+j]->setStyleSheet("background:gray;font-size:20px");

    for(int i=57;i<=59;++i)
        for(int j=0;j<=18;j+=9)
            btn_sudoku[i+j]->setStyleSheet("background:gray;font-size:20px");
}
void MainWindow::easy_click()
{
    Sudoku ques;
    Sudoku ans;
    int num,if_generate[10]={0};
    srand(time(NULL));
    for(int i=0;i<=8;++i) //generate random seed
    {
        num=rand()%9+1;
        while(if_generate[num])
            num=rand()%9+1;
        if_generate[num]=1;
        ques.setElement(i*10, num);
    }

    solve(ques,ans);
    correct_ans=ans;
    Sudoku title=ans;
    bool hole[81]={0};
    int hole_num=43,index;
    for(int i=0;i<hole_num;++i)
    {
        index=rand()%81;
        while(hole[index])
            index=rand()%81;
        hole[index]=1;
        title.setElement(index,0);
    }
    for(int i=0;i<81;++i)
    {
        btn_sudoku[i]->num=title.getElement(i);
        if(title.getElement(i)==0)
            btn_sudoku[i]->setText("");
        else
        {
            btn_sudoku[i]->setText(QString::number(title.getElement(i)));
            btn_sudoku[i]->setStyleSheet("background:yellow;font-size:20px");
            btn_sudoku[i]->judge=1;
        }

    }

    btn_hard->hide();
    btn_normal->hide();
    btn_easy->hide();
    btn_complete->show();
    btn_ans->show();
}

void MainWindow::hard_click()
{
    Sudoku ques;
    Sudoku ans;
    int num,if_generate[10]={0};
    srand(time(NULL));
    for(int i=0;i<=8;++i) //generate random seed
    {
        num=rand()%9+1;
        while(if_generate[num])
            num=rand()%9+1;
        if_generate[num]=1;
        ques.setElement(i*10, num);
    }

    solve(ques,ans);
    correct_ans=ans;
    Sudoku title=ans;
    bool hole[81]={0};
    int hole_num=56,index;
    for(int i=0;i<hole_num;++i)
    {
        index=rand()%81;
        while(hole[index])
            index=rand()%81;
        hole[index]=1;
        title.setElement(index,0);
    }
    for(int i=0;i<81;++i)
    {
        btn_sudoku[i]->num=title.getElement(i);
        if(title.getElement(i)==0)
            btn_sudoku[i]->setText("");
        else
        {
            btn_sudoku[i]->setText(QString::number(title.getElement(i)));
            btn_sudoku[i]->setStyleSheet("background:yellow;font-size:20px");
            btn_sudoku[i]->judge=1;
        }
    }

    btn_hard->hide();
    btn_normal->hide();
    btn_easy->hide();
    btn_complete->show();
    btn_ans->show();
}

void MainWindow::normal_click()
{
    Sudoku ques;
    Sudoku ans;
    int num,if_generate[10]={0};
    srand(time(NULL));
    for(int i=0;i<=8;++i) //generate random seed
    {
        num=rand()%9+1;
        while(if_generate[num])
            num=rand()%9+1;
        if_generate[num]=1;
        ques.setElement(i*10, num);
    }

    solve(ques,ans);
    correct_ans=ans;
    Sudoku title=ans;
    bool hole[81]={0};
    int hole_num=51,index;
    for(int i=0;i<hole_num;++i)
    {
        index=rand()%81;
        while(hole[index])
            index=rand()%81;
        hole[index]=1;
        title.setElement(index,0);
    }
    for(int i=0;i<81;++i)
    {
        if(title.getElement(i)==0)
            btn_sudoku[i]->setText("");
        else
        {
            btn_sudoku[i]->setText(QString::number(title.getElement(i)));
            btn_sudoku[i]->setStyleSheet("background:yellow;font-size:20px");
            btn_sudoku[i]->judge=1;
        }
    }

    btn_hard->hide();
    btn_normal->hide();
    btn_easy->hide();
    btn_complete->show();
    btn_ans->show();
}

void MainWindow::compelete_click()
{
    Sudoku your_ans;
    for(int i=0;i<81;i++)
    {
        your_ans.setElement(i,btn_sudoku[i]->num);
    }
    if(your_ans.isCorrect())
    {
        solution_result->show();
        solution_result->setText("Congratulation");
        solution_result->setStyleSheet("color:green;font-size:40px;");
    }
    else
    {
        solution_result->show();
        solution_result->setText("Wrong");
        solution_result->setStyleSheet("color:red;font-size:40px;");
    }
}

void MainWindow::ans_click()
{
    for(int i=0;i<81;i++)
    {
        btn_sudoku[i]->setText(QString::number(correct_ans.getElement(i)));
        btn_sudoku[i]->num=correct_ans.getElement(i);
    }
}
void MainWindow::if_vis(Sudoku question, int index)
{
        for(int i=0;i<10;i++)//initiation
            arr[i]=0;

        for(int i=index-index%9 ; i<=(index-index%9+8);++i)//check row
        {
            int x=question.getElement(i);
            if(x)
                arr[x]=1;
        }

        for(int i=index%9;i<=80;i+=9)//check column
        {
            int x=question.getElement(i);
            if(x)
                arr[x]=1;
        }


        index=9*(index/9-index/9%3)+(index%9-index%9%3);//left up of cell
        for(int i=index;i<index+3;i++)//check cell
        {
            for(int d=0;d<=18;d+=9)
            {
                int x=question.getElement(i+d);
                if(x)
                    arr[x]=1;
            }
        }

}

bool MainWindow::solve(Sudoku question, Sudoku &answer)
{
    int firstZero;
    bool check[10];
    firstZero = question.getFirstZeroIndex();
    if(firstZero == -1)
    { // end condition
        if(question.isCorrect())
        {
            answer = question;
            return true;
        }
        else
            return false;
    }
    else
    {

        if_vis(question,firstZero);
        for(int i=1;i<=9;++i)
            check[i]=arr[i];
        for(int num=1; num<=9; ++num)
        {
            //if_vis(question,firstZero);
            if(!check[num])//if num doesn't vis
            {
                question.setElement(firstZero, num);
                if(solve(question, answer))
                    return true;
            }
        }
        return false;
    }

}

bool MainWindow::if_legal(Sudoku question)
{
    for(int i=0;i<=72;i+=9)//check if row legal
        {
            int row_check[10]={0};
            for(int j=0;j<9;j++)
            {
                int x=question.getElement(i+j);
                if(x)
                {
                    if(row_check[x]==1) return false;
                    else row_check[x]++;
                }
            }
        }

        for(int i=0;i<=8;i++)//check if column legal
        {
            int column_check[10]={0};
            for(int j=0;j<=72;j+=9)
            {
                int x=question.getElement(i+j);
                if(x)
                {
                    if(column_check[x]==1) return false;
                    else column_check[x]++;
                }
            }
        }

        for(int k=0;k<3;k++)//check if cell legal
        {
            int cell_check[10]={0};
            for(int i=3*k, t=0 ; t<3 ;i++,t++)
            {
                for(int j=0;j<=18;j+=9)
                {
                    int x=question.getElement(i+j);
                    if(x)
                    {
                        if(cell_check[x]==1) return false;
                        else cell_check[x]++;
                    }
                }
            }
        }

        for(int k=0;k<3;k++)//check if cell legal
        {
            int cell_check[10]={0};
            for(int i=27+3*k, t=0 ; t<3 ;i++,t++)
            {
                for(int j=0;j<=18;j+=9)
                {
                    int x=question.getElement(i+j);
                    if(x)
                    {
                        if(cell_check[x]==1) return false;
                        else cell_check[x]++;
                    }
                }
            }
        }


        for(int k=0;k<3;k++)//check if cell legal
        {
            int cell_check[10]={0};
            for(int i=54+3*k, t=0 ; t<3 ;i++,t++)
            {
                for(int j=0;j<=18;j+=9)
                {
                    int x=question.getElement(i+j);
                    if(x)
                    {
                        if(cell_check[x]==1) return false;
                        else cell_check[x]++;
                    }
                }
            }
        }

        return true;

}
