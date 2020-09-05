#include "sudoku.h"                                                                                                                          
using namespace std;

Sudoku::Sudoku()
{
    for(int i=0; i<sudokuSize; ++i)
        map[i] = 0;
}
Sudoku::Sudoku(const int init_map[])
{
    for(int i=0; i<sudokuSize; ++i)
        map[i] = init_map[i];
}

void Sudoku::setMap(const int set_map[])
{
    for(int i=0; i<sudokuSize; ++i)
        map[i] = set_map[i];
}

int Sudoku::getElement(int index)
{
    return map[index];
}

void Sudoku::setElement(int index, int value)
{
    map[index] = value;
}

int Sudoku::getFirstZeroIndex()
{
    for(int i=0;i<sudokuSize;++i)
        if(map[i] == 0)
            return i;
    return -1;
}

bool Sudoku::checkUnity(int arr[])
{
    int arr_unity[9]; // counters

    for(int i=0; i<9; ++i)
        arr_unity[i] = 0; // initialize
    for(int i=0; i<9; ++i)
        ++arr_unity[arr[i]-1]; // count
    for(int i=0; i<9; ++i)
        if(arr_unity[i] != 1) // all element
            return false; // must be 1
    return true;
}

bool Sudoku::isCorrect()
{
    bool check_result;
    int check_arr[9];
    int location;
    for(int i=0; i<81; i+=9) // check rows
    {
        for(int j=0; j<9; ++j)
            check_arr[j] = map[i+j];
        check_result = checkUnity(check_arr);
        if(check_result == false)
            return false;
    }
    for(int i=0; i<9; ++i) // check columns
    {
        for(int j=0; j<9; ++j)
        check_arr[j] = map[i+9*j];
        check_result = checkUnity(check_arr);
        if(check_result == false)
            return false;
    }

    for(int i=0; i<9; ++i) // check cells
    {
        for(int j=0; j<9; ++j)
        {
            location = 27*(i/3) + 3*(i%3) +9*(j/3) + (j%3);
            check_arr[j] = map[location];
        }
        check_result = checkUnity(check_arr);
        if(check_result == false)
            return false;
    }
    return true;
}
