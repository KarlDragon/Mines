#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>
using namespace std;
//TODO Tao bang min
void generateBombMap(int board[],int rows,int cols,int bombcount)
{
    int  size = rows * cols;
    for (int  i = 0; i < rows * cols; i++)
    {
        board[i]= 0;
    }
    srand(time(NULL));
    int count = 0;
    if ( bombcount > size) 
    {
        bombcount = size;
    }
    while ( count < bombcount ) 
    {
        int pos = rand() % size;
    }
    if (board[pos] == 0) {
        board[pos] = -1;
        count++;
    }
}

// TODO Tinh so min lan can
void calculateBombNumbers(int board[], int rows, int cols) 


int main(){
    return 0;
}