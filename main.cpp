#include <bits/stdc++.h>
#include <iostream>
using namespace std;

//const int MAX_SIZE = 100;

bool checkIsBomb(int row, int col, bool arr[][]);
bool checkIsRevealed(int row, int col, bool arr[][]);
bool checkIsFlagged(int row, int col, bool arr[][]);

int main() {
    int rows, cols;

    cout << "Nhap so hang : ";
    cin >> rows;
    cout << "Nhap so cot : ";
    cin >> cols;
    cout << endl;
    //if (rows <= 0 || rows > MAX_SIZE || cols <= 0 || cols > MAX_SIZE) {
        //cout << "Kich thuoc khong hop le!\n";
       // return 1;
    //}
    bool isBomb[MAX_SIZE][MAX_SIZE];
    bool isRevealed[MAX_SIZE][MAX_SIZE];
    bool isFlagged[MAX_SIZE][MAX_SIZE];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            isBomb[i][j] = false;
            isRevealed[i][j] = false;
            isFlagged[i][j] = false;
        }
    }

    //isBomb[2][3] = true;
    //isRevealed[5][4] = true;
    //isFlagged[8][13] = true;

    //cout << (checkIsBomb(2, 3, isBomb, rows, cols) ? "TRUE (Dung!)" : "FALSE (Sai!)") << endl;
   // cout << (checkIsBomb(0, 0, isBomb, rows, cols) ? "TRUE (Dung!)" : "FALSE (Sai!)") << endl;
    //cout << (checkIsRevealed(5, 4, isRevealed, rows, cols) ? "TRUE (Dung!)" : "FALSE (Sai!)") << endl;
    //cout << (checkIsRevealed(1, 1, isRevealed, rows, cols) ? "TRUE (Dung!)" : "FALSE (Sai!)") << endl;
   // cout << (checkIsFlagged(8, 13, isFlagged, rows, cols) ? "TRUE (Dung!)" : "FALSE (Sai!)") << endl;
    //cout << (checkIsFlagged(0, 4, isFlagged, rows, cols) ? "TRUE (Dung!)" : "FALSE (Sai!)") << endl;
}

bool checkIsBomb(int row, int col, bool arr[][], int rows, int cols) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return false;
    }
    return arr[row][col];
}

bool checkIsRevealed(int row, int col, bool arr[][], int rows, int cols) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return false;
    }
    return arr[row][col];
}

bool checkIsFlagged(int row, int col, bool arr[][], int rows, int cols) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return false;
    }
    return arr[row][col];
}
