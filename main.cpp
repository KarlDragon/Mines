#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>
using namespace std;
//TODO Tạo bảng mìn
void generateBombMap(int board[],int rows,int cols,int bombcount)  {
    for (int  i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++) {
            board[i]= 0;
        }
    }
    srand(time(NULL));
    int count = 0;
    if ( bombcount > size) {
        bombcount = size;
    }
    While ( count < bombcount ) {
        int pos = rand() % size;
        if (board[pos] == 0) {
            board[pos] = -1;
            count++;
        }
    }
}

int main(){
    return 0;
}