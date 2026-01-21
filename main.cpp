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
//click
void handleCellClick(int row, int col, int clickType)
{
    // kiem tra bien
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS)
        return;

    // click trai
    if (clickType == 0)
    {
        // neu o da mo hoac co co thi bo qua
        if (revealedArray[row][col] || flaggedArray[row][col])
            return;

        // neu o do la bom thi thua
        if (bombMap[row][col] == -1)
        {
            revealedArray[row][col] = true;

            MessageBoxA(NULL, " ban da thua game!", "GAME OVER", MB_OK);
            PostQuitMessage(0);
            return;
        }

        // neu value>0 thi mo o
        if (bombNumbers[row][col] > 0)
        {
            revealedArray[row][col] = true;
            return;
        }

        // neu value==0 thi mo o va mo lan
        floodFill(row, col);
    }

    // click phai
    if (clickType == 1)
    {
        // chi cho cam co khi o chua mo
        if (!revealedArray[row][col] && FLAG_COUNT > 0)
        {
            flaggedArray[row][col] = !flaggedArray[row][col];

            if (flaggedArray[row][col])
                FLAG_COUNT--;
            else
                FLAG_COUNT++;
        }
    }
}
// khoi tao game
void gameInit(){
    ROWS = 10;
    COLS = 10;
    BOMB_COUNT = 15;
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

// ve bang min
void drawBoard(HDC hdc)
{
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            int x1 = BOARD_OFFSET_X + c * CELL_SIZE;
            int y1 = BOARD_OFFSET_Y + r * CELL_SIZE;
            int x2 = x1 + CELL_SIZE;
            int y2 = y1 + CELL_SIZE;

            Rectangle(hdc, x1, y1, x2, y2);
        }
    }
}
// ve thoi gian + so co
void drawInfo(HDC hdc)
{
    // tao buffer de chua tam du lieu
    char buffer[64];

    // info thoi gian
    // viet du lieu vao buffer
    sprintf(buffer, "Time: %d", elapsedSeconds);
    // hien thi buffer len window
    // tham so lan luot la : hdc, vi tri x, vi tri y, chuoi ky tu, do dai chuoi
    TextOutA(hdc, 10, 10, buffer, strlen(buffer));

    // info so co
    sprintf(buffer, "Flags: %d", FLAG_COUNT);
    TextOutA(hdc, 150, 10, buffer, strlen(buffer));
}

// code UI
// Ham xu ly su kien cua window
LRESULT CALLBACK WindowProc(
    HWND hwnd, // Handle cua window ( id cua window )
    UINT msg, // Ma su kien
    WPARAM wParam, // Tham so thu 1 ( phim bam, ... )
    LPARAM lParam // Tham so thu 2 ( vi tri con tro chuot, ...)
)
{
    // Xu ly su kien
    switch (msg)
    {
    // case ve window
    case WM_PAINT:
    {
        
        PAINTSTRUCT ps;
        // hdc = "bút vẽ" của window
        HDC hdc = BeginPaint(hwnd, &ps);

        // Vẽ bảng mìn
        drawBoard(hdc);

        // Vẽ thông tin thời gian và số cờ
        drawInfo(hdc);

        // Kết thúc vẽ
        EndPaint(hwnd, &ps);
        
        return 0;
    }
    // case xu ly timer
    case WM_TIMER:
    {
        // Cap nhat thoi gian
        elapsedSeconds++;
        InvalidateRect(hwnd, NULL, TRUE); // vẽ lại
        return 0;
    }
         // Click chuot trai - mo o
    case WM_LBUTTONDOWN:
    {
        if (GAME_OVER) return 0;

        int xPos = LOWORD(lParam);
        int yPos = HIWORD(lParam);

        // Tính toán row, col từ vị trí chuột
        int col = (xPos - BOARD_OFFSET_X) / CELL_SIZE;
        int row = (yPos - BOARD_OFFSET_Y) / CELL_SIZE;

        // Kiểm tra xem click có trong bảng không
        if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
            handleCellClick(row, col, 0);
            InvalidateRect(hwnd, NULL, TRUE);
        }
        return 0;
    }

    // Click chuot phai - cam co
    case WM_RBUTTONDOWN:
    {
        if (GAME_OVER) return 0;

        int xPos = LOWORD(lParam);
        int yPos = HIWORD(lParam);

        int col = (xPos - BOARD_OFFSET_X) / CELL_SIZE;
        int row = (yPos - BOARD_OFFSET_Y) / CELL_SIZE;

        if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
            // Chỉ cắm cờ khi ô chưa được mở
            if (!isRevealed(row, col, revealedArray)) {
                if (isFlagged(row, col, flaggedArray)) {
                    // Gỡ cờ
                    flaggedArray[row][col] = false;
                    FLAG_COUNT++;
                } else {
                    // Cắm cờ
                    if (FLAG_COUNT > 0) {
                        flaggedArray[row][col] = true;
                        FLAG_COUNT--;
                    }
                }
                InvalidateRect(hwnd, NULL, TRUE);
            }
        }
        return 0;
    }

    case WM_DESTROY:
        // Khi window bi dong
        PostQuitMessage(0);
        return 0;
    }

    // Su kien mac dinh
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

// Ham chinh cua ung dung
int WINAPI WinMain(
    HINSTANCE hInstance, // Handle cua ung dung
    HINSTANCE, // Handle cua ung dung goi no ( khong su dung )
    LPSTR, // Tham so dong lenh ( khong su dung )
    int nCmdShow // Che do hien thi cua window
)
{
    // Khoi tao game
    gameInit();
    // Dang ky lop cua window
    // Ten lop window
    const char CLASS_NAME[] = "MyWindowClass";

    // Cua so lop
    // Khai bao va khoi tao cau truc WNDCLASSA
    WNDCLASSA wc = {};
    //ham xu ly su kien
    wc.lpfnWndProc = WindowProc;
    // gan hInstance voi window hien tai
    wc.hInstance = hInstance;
    // ten lop window
    wc.lpszClassName = CLASS_NAME;

    // dang ky lop window
    if (!RegisterClassA(&wc))
    {
        MessageBoxA(NULL, "RegisterClass FAILED", "ERROR", MB_ICONERROR);
        return 0;
    }
    // Tao window
    HWND hwnd = CreateWindowExA(
        0, // Kieu mo rong cua window
        CLASS_NAME, // Ten lop window
        "Hello Windows", // Tieu de cua window
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, // Kieu cua window ( vd : co thanh tieu de, co the thay doi kich thuoc, ... )
        CW_USEDEFAULT, // Vi tri x cua window
        CW_USEDEFAULT, // Vi tri y cua window
        WINDOW_WIDTH, // Chieu rong cua window
        WINDOW_HEIGHT, // Chieu cao cua window
        NULL, // Handle cua window cha ( NULL neu la window chinh )
        NULL, // Handle cua menu ( NULL neu khong co menu )
        hInstance, // Handle cua ung dung
        NULL // Tham so khoi tao ( khong su dung )
    );

    // Kiem tra tao window co thanh cong khong
    if (hwnd == NULL)
    {
        MessageBoxA(NULL, "CreateWindowEx failed", "ERROR", MB_ICONERROR);
        return 0;
    }

    // Hien thi window
    ShowWindow(hwnd, nCmdShow);
    // khoi dong timer
    SetTimer(hwnd, timerId, 1000, NULL);
    // Cap nhat window
    UpdateWindow(hwnd); 
    // Chuong trinh chinh cua message loop
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        // Chuyen thong diep
        TranslateMessage(&msg);
        
        // Gui thong diep den ham xu ly su kien
        DispatchMessage(&msg);
    }


}
