#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>
using namespace std;
//TODO Tao bang min
void generateBombMap(int board[],int rows,int cols,int bombcount)  {
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
void calculateBombNumbers(int board[], int rows, int cols) {
    for (int r = 0; r < rows; r++) 
    {
        for (int c = 0; c < cols; c++) 
        {
            int index = r * cols + c;
            if (board[index] == -1) 
            {
                continue;
            }
            int bombcount = 0;
            for (int i = -1; i <= 1; i++) 
            {
                for (int j = -1; j <= 1;j++) 
                {
                    if (i == 0 && j == 0) 
                    {
                        continue;
                    }
                    int newrow = r + i;
                    int newcol = c + j;
                    if (newrow >= 0 && newrow < rows && newcol >= 0 && newcol < cols) 
                    {
                        int newindex = newrow * cols + newcol;
                        if (board[newindex] == -1) 
                        {
                            bombcount++;
                        }
                    } 
                }
            }
        }
        board[index] = bombcount;
    }
}

int main(){
    return 0;
}