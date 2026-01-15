#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;
//TODO Tao bang min
vector<vector<int>> generateBombMap(int rows, int cols, int bombCount) {
    vector<vector<int>> board(rows, vector<int>(cols, 0));

    srand(time(nullptr));
    int placedBombs = 0;

    while (placedBombs < bombCount) {
        int r = rand() % rows;
        int c = rand() % cols;

        if (board[r][c] == 0) {
            board[r][c] = -1;
            placedBombs++;
        }
    }

    return board;
}
// TODO Tinh so min lan can
vector<vector<int>> calculateBombNumbers(const vector<vector<int>>& board) {
    int rows = board.size();
    int cols = board[0].size();

    vector<vector<int>> result = board;

    int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            if (board[i][j] == -1) continue;

            int bombCount = 0;

            for (int k = 0; k < 8; k++) {
                int ni = i + dx[k];
                int nj = j + dy[k];

                if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                    if (board[ni][nj] == -1) {
                        bombCount++;
                    }
                }
            }

            result[i][j] = bombCount;
        }
    }

    return result;
}
//Mang Revealed
vector<vector<bool>> createRevealed(int row, int column) {
    return vector<vector<bool>>(row, vector<bool>(column, false));
}

//Mang Flagged
vector<vector<bool>> createFlagged(int row, int column) {
    return vector<vector<bool>>(row, vector<bool>(column, false));
}

//check bom
bool isBomb(int row, int column, const vector<vector<bool>>& revealedArray) {
    if (row < 0 || row >= revealedArray.size() ||
        column < 0 || column >= revealedArray[0].size()) {
        return false;
    }
    return revealedArray[row][column];
}

//check o 
bool isRevealed(int row, int column, const vector<vector<bool>>& revealedArray) {
    if (row < 0 || row >= revealedArray.size() ||
        column < 0 || column >= revealedArray[0].size()) {
        return false;
    }
    return revealedArray[row][column];
}

//check cam co
bool isFlagged(int row, int column, const vector<vector<bool>>& flaggedArray) {
    if (row < 0 || row >= flaggedArray.size() ||
        column < 0 || column >= flaggedArray[0].size()) {
        return false;
    }
    return flaggedArray[row][column];
}



int main() {
    //tao mang
    //vector<vector<bool>> revealedArray = createRevealed(5, 5);
    //vector<vector<bool>> flaggedArray = createFlag