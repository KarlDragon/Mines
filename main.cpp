#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

// tao bien toan cuc
int ROWS;
int COLS;
int BOMB_COUNT;
int FLAG_COUNT;
int CELL_SIZE;
int BOARD_OFFSET_X;
int BOARD_OFFSET_Y;
int WINDOW_WIDTH;
int WINDOW_HEIGHT;
int elapsedSeconds;
UINT_PTR timerId;
//tao mang
vector<vector<bool>> revealedArray;
vector<vector<bool>> flaggedArray;

// Mang chua tinh so bom
vector<vector<int>> bombMap;
// Mang da tinh so bom lan can
vector<vector<int>> bombNumbers;

// TODO Tao bang min
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
//mo rong o
void revealEmptyCells(int currentRow,int currentColumn, vector<vector<int>>& bombNumbers, vector<vector<bool>>& revealedArray,int ROWS,int COLS){
    if (currentRow<0||currentRow>=ROWS||currentColumn<0||currentColumn>=COLS) return;
    if(revealedArray[currentRow][currentColumn])
        return;
    revealedArray[currentRow][currentColumn]=true;
    if(bombNumbers[currentRow][currentColumn]!=0)
        return;
    int dx[8] = {-1,-1,-1,0,0,1,1,1};
    int dy[8] = {-1,0,1,-1,1,-1,0,1};
    for (int k=0;k<8;k++){
        revealEmptyCells(currentRow+dx[k],currentColumn+dy[k],bombNumbers,revealedArray,ROWS,COLS);
    }
    //gei
}


// khoi tao game
void gameInit(){
    ROWS = 10;
    COLS = 10;
    BOMB_COUNT = 5;
    FLAG_COUNT = BOMB_COUNT;
    // kich thuoc o
    CELL_SIZE = 30;
    // vi tri bang min
    BOARD_OFFSET_X = 10;
    BOARD_OFFSET_Y = 50;
    // tinh kich thuoc window
    WINDOW_WIDTH = BOARD_OFFSET_X * 2 + COLS * CELL_SIZE;
    WINDOW_HEIGHT = BOARD_OFFSET_Y * 2 + ROWS * CELL_SIZE;
    // khoi tao thoi gian
    elapsedSeconds = 0;
    timerId = 1;
    // khoi tao bang min
    bombMap = generateBombMap(ROWS, COLS, BOMB_COUNT);
    bombNumbers = calculateBombNumbers(bombMap);
    revealedArray = createRevealed(ROWS, COLS);
    flaggedArray = createFlagged(ROWS, COLS);
}

// code UI
// Ham xu ly su kien cua window

int main() {
    // khoi tao game
    gameInit();

    // test
    for (const auto& row : bombNumbers) {
        for (const auto& cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }

    revealEmptyCells(2,3,bombNumbers,revealedArray,ROWS,COLS);
    for (const auto& row : revealedArray) {
        for (const auto& cell : row) {
            cout << (cell ? "R " : ". ");
        }
        cout << endl;
    }
}
