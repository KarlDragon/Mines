#include <bits/stdc++.h>
#include <iostream>
using namespace std;
const int MAX_SIZE = 100;
bool checkIsBomb(int row, int col, bool arr[][MAX_SIZE], int rows, int cols);
bool checkIsRevealed(int row, int col, bool arr[][MAX_SIZE], int rows, int cols);
bool checkIsFlagged(int row, int col, bool arr[][MAX_SIZE], int rows, int cols);
int main() {
    int rows, cols;
    cout << "Nhap so hang (toi da " << MAX_SIZE << "): ";
    cin >> rows;
    cout << "Nhap so cot (toi da " << MAX_SIZE << "): ";
    cin >> cols;
    cout << endl;
    if (rows <= 0 || rows > MAX_SIZE || cols <= 0 || cols > MAX_SIZE) {
        cout << "Loi, kich thuoc khong hop le\n";
        cout << "Hay nhap so tu 1 den " << MAX_SIZE << endl;
        return 1;
    }
    bool isBomb[MAX_SIZE][MAX_SIZE];       // Mang luu thong tin min
    bool isRevealed[MAX_SIZE][MAX_SIZE];   // Mang luu thong o da mo
    bool isFlagged[MAX_SIZE][MAX_SIZE];    // Mang luu thong da cam co
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            isBomb[i][j] = false;
            isRevealed[i][j] = false;
            isFlagged[i][j] = false;
        }
    }
    isBomb[5][2] = true;          
    isRevealed[4][6] = true;      
    isFlagged[3][1] = true;
    cout << (checkIsBomb(0, 0, isBomb, rows, cols) ? "TRUE (Dung!)" : "FALSE (Sai!)") << endl;
    cout << (checkIsBomb(5, 2, isBomb, rows, cols) ? "TRUE (Dung!)" : "FALSE (Sai!)") << endl;
    cout << (checkIsRevealed(11, 12,isRevealed, rows, cols) ? "TRUE (Dung!)" : "FALSE (Sai!)") << endl;
    cout << (checkIsRevealed(4, 6, isRevealed, rows, cols) ? "TRUE (Dung!)" : "FALSE (Sai!)") << endl;
    cout << (checkIsFlagged(50, 20, isFlagged, rows, cols) ? "TRUE (Dung!)" : "FALSE (Sai!)") << endl;
    cout << (checkIsFlagged(3, 1, isFlagged, rows, cols) ? "TRUE (Dung!)" : "FALSE (Sai!)") << endl;
    




}
bool checkIsBomb(int row, int col, bool arr[][MAX_SIZE], int rows, int cols) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return false;
    }
    return arr[row][col];
}
bool checkIsRevealed(int row, int col, bool arr[][MAX_SIZE], int rows, int cols) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return false;
    }
    return arr[row][col];
}
bool checkIsFlagged(int row, int col, bool arr[][MAX_SIZE], int rows, int cols) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return false;
    }
    return arr[row][col];
}
