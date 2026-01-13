#include <iostream>
#include <vector>
using namespace std;

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
    vector<vector<bool>> revealedArray = createRevealed(5, 5);
    revealedArray[2][3] = true; // Example of revealing a cell
    cout << "Cell (2,3) revealed: " << isRevealed(2, 3, revealedArray) << endl;
    //vector<vector<bool>> flaggedArray = createFlagged(5, 5);
}
