#include <windows.h>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;
// Build code dùng lệnh sau trong terminal:
// g++ main.cpp -o app -lgdi32 -luser32 
// -lgdi32: thư viện đồ họa
// -luser32: thư viện cửa sổ
// sau đó mở file app.exe để chạy ứng dụng

// tao bien toan cuc
int ROWS;
int COLS;
int BOMB_COUNT;
int FLAG_COUNT;
int REMAINING_CELLS;
int CELL_SIZE;
int BOARD_OFFSET_X;
int BOARD_OFFSET_Y;
int WINDOW_WIDTH;
int WINDOW_HEIGHT;
int elapsedSeconds;
int INFO_HEIGHT;
const int STATE_MENU = 0;
const int STATE_PLAYING = 1;
const int STATE_GAMEOVER = 2;
const int STATE_WIN = 3;

int gameState;

// Button RECT
RECT btnEasy, btnMedium, btnHard, btnRestart, btnMenu;

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
    REMAINING_CELLS--;
    if(bombNumbers[currentRow][currentColumn]!=0)
        return;
    int dx[8] = {-1,-1,-1,0,0,1,1,1};
    int dy[8] = {-1,0,1,-1,1,-1,0,1};
    for (int k=0;k<8;k++){
        revealEmptyCells(currentRow+dx[k],currentColumn+dy[k],bombNumbers,revealedArray,ROWS,COLS);
    }
}
// Ham xu ly click vao o
void handleCellClick(int row, int col, int clickType) {
    // Click trai (clickType = 0)
    if (clickType == 0) {
        // Neu o da mo hoac co cam co -> bo qua
        if (isRevealed(row, col, revealedArray) || isFlagged(row, col, flaggedArray)) {
            return;
        }

        // Neu la bom -> thua game
        if (bombMap[row][col] == -1) {
            gameState = STATE_GAMEOVER;
            // Mo tat ca cac o
            for (int r = 0; r < ROWS; r++) {
                for (int c = 0; c < COLS; c++) {
                    revealedArray[r][c] = true;
                }
            }
            return;
        }

        // Neu value > 0 -> mo o
        if (bombNumbers[row][col] > 0) {
            revealedArray[row][col] = true;
            REMAINING_CELLS--;
            // Kiem tra thang game
            if (REMAINING_CELLS == 0) {
                gameState = STATE_WIN;
            }
        }
        // Neu value == 0 -> mo o + mo lan cac o xung quanh (flood fill)
        else if (bombNumbers[row][col] == 0) {
            revealEmptyCells(row, col, bombNumbers, revealedArray, ROWS, COLS);
        }
    }
}


// khoi tao game
void gameInit(){
    REMAINING_CELLS = ROWS * COLS - BOMB_COUNT;
    FLAG_COUNT = BOMB_COUNT;
    // kich thuoc o
    CELL_SIZE = 30;
    INFO_HEIGHT = 40;
    // vi tri bang min
    BOARD_OFFSET_X = 20;
    BOARD_OFFSET_Y = 50;
    // tinh kich thuoc window
    WINDOW_WIDTH = BOARD_OFFSET_X * 2 + COLS * CELL_SIZE;
    WINDOW_HEIGHT = BOARD_OFFSET_Y * 2 + ROWS * CELL_SIZE;
    // khoi tao thoi gian
    elapsedSeconds = 0;
    // khoi tao bang min
    bombMap = generateBombMap(ROWS, COLS, BOMB_COUNT);
    bombNumbers = calculateBombNumbers(bombMap);
    revealedArray = createRevealed(ROWS, COLS);
    flaggedArray = createFlagged(ROWS, COLS);
}

// resize window
void resizeWindowToBoard(HWND hwnd)
{
    RECT rect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };

    // Tinh kich thuoc window chua ca khung
    AdjustWindowRect(
        &rect,
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        FALSE
    );
    // Thay doi kich thuoc window
    SetWindowPos(
        hwnd,
        NULL,
        0, 0,
        rect.right - rect.left,
        rect.bottom - rect.top,
        SWP_NOMOVE | SWP_NOZORDER
    );
}
// dat do kho
void setDifficulty(string level, HWND hwnd)
{
    if (level == "EASY") {
        ROWS = 9;
        COLS = 9;
        BOMB_COUNT = 10;
    }
    else if (level == "MEDIUM") {
        ROWS = 16;
        COLS = 16;
        BOMB_COUNT = 40;
    }
    else if (level == "HARD") {
        ROWS = 16;
        COLS = 30;
        BOMB_COUNT = 99;
    }

    gameState = STATE_PLAYING;
    gameInit();

    resizeWindowToBoard(hwnd);
}

// Mau cho cac so
COLORREF getNumberColor(int num) {
    switch (num) {
        case 1: return RGB(0, 0, 255);       // Blue
        case 2: return RGB(0, 128, 0);       // Green
        case 3: return RGB(255, 0, 0);       // Red
        case 4: return RGB(0, 0, 128);       // Dark Blue
        case 5: return RGB(128, 0, 0);       // Dark Red
        case 6: return RGB(0, 128, 128);     // Teal
        case 7: return RGB(0, 0, 0);         // Black
        case 8: return RGB(128, 128, 128);   // Gray
        default: return RGB(0, 0, 0);
    }
}

void drawMenu(HWND hwnd, HDC hdc)
{
    RECT client;
    GetClientRect(hwnd, &client);

    FillRect(hdc, &client, (HBRUSH)(COLOR_WINDOW + 1));

    SetBkMode(hdc, TRANSPARENT);

    HFONT hTitleFont = CreateFont(36, 0, 0, 0, FW_BOLD,
                                 FALSE, FALSE, FALSE,
                                 DEFAULT_CHARSET,
                                 OUT_DEFAULT_PRECIS,
                                 CLIP_DEFAULT_PRECIS,
                                 DEFAULT_QUALITY,
                                 DEFAULT_PITCH | FF_SWISS,
                                 "Arial");

    HFONT oldFont = (HFONT)SelectObject(hdc, hTitleFont);

    DrawTextA(
        hdc,
        "MINESWEEPER",
        -1,
        &client,
        DT_CENTER | DT_TOP
    );

    int btnWidth = 200;
    int btnHeight = 40;
    int centerX = (client.right - btnWidth) / 2;

    btnEasy = { centerX, 120, centerX + btnWidth, 160 };
    btnMedium = { centerX, 180, centerX + btnWidth, 220 };
    btnHard = { centerX, 240, centerX + btnWidth, 280 };

    Rectangle(hdc, btnEasy.left, btnEasy.top, btnEasy.right, btnEasy.bottom);
    DrawTextA(hdc, "Easy", -1, &btnEasy, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    Rectangle(hdc, btnMedium.left, btnMedium.top, btnMedium.right, btnMedium.bottom);
    DrawTextA(hdc, "Medium ", -1, &btnMedium, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    Rectangle(hdc, btnHard.left, btnHard.top, btnHard.right, btnHard.bottom);
    DrawTextA(hdc, "Hard", -1, &btnHard, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    SelectObject(hdc, oldFont);
    DeleteObject(hTitleFont);

}
// ve bang min 
void drawBoard(HDC hdc)
{
    // Font cho so
    HFONT hFont = CreateFont(16, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                             DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                             DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
    HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

    // Căn giữa text
    SetTextAlign(hdc, TA_CENTER | TA_BASELINE);
    SetBkMode(hdc, TRANSPARENT);

    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            int x1 = BOARD_OFFSET_X + c * CELL_SIZE;
            int y1 = BOARD_OFFSET_Y + r * CELL_SIZE;
            int x2 = x1 + CELL_SIZE;
            int y2 = y1 + CELL_SIZE;

            // Vẽ khung ô
            Rectangle(hdc, x1, y1, x2, y2);

            // Tô màu nền cho ô đã mở
            if (revealedArray[r][c]) {
                HBRUSH hBrush = CreateSolidBrush(RGB(220, 220, 220));
                HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
                Rectangle(hdc, x1 + 1, y1 + 1, x2 - 1, y2 - 1);
                SelectObject(hdc, hOldBrush);
                DeleteObject(hBrush);

                // Vẽ số nếu có bom lân cận
                if (bombNumbers[r][c] > 0) {
                    char buffer[8];
                    sprintf(buffer, "%d", bombNumbers[r][c]);
                    SetTextColor(hdc, getNumberColor(bombNumbers[r][c]));
                    TextOutA(hdc, (x1 + x2) / 2, (y1 + y2) / 2 + 5, buffer, strlen(buffer));
                }
                // Vẽ bom nếu là ô bom
                else if (bombMap[r][c] == -1) {
                    SetTextColor(hdc, RGB(255, 0, 0));
                    TextOutA(hdc, (x1 + x2) / 2, (y1 + y2) / 2 + 5, "*", 1);
                }
            }
            // Ô chưa mở
            else {
                // Tô màu xám
                HBRUSH hBrush = CreateSolidBrush(RGB(180, 180, 180));
                HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
                Rectangle(hdc, x1 + 1, y1 + 1, x2 - 1, y2 - 1);
                SelectObject(hdc, hOldBrush);
                DeleteObject(hBrush);

                // Vẽ cờ nếu có
                if (flaggedArray[r][c]) {
                    SetTextColor(hdc, RGB(255, 0, 0));
                    TextOutA(hdc, (x1 + x2) / 2, (y1 + y2) / 2 + 5, "F", 1);
                }
            }
        }
    }
    // Khôi phục font cũ
    SelectObject(hdc, hOldFont);
    DeleteObject(hFont);
}

void drawInfo(HWND hwnd, HDC hdc)
{
    RECT client;
    GetClientRect(hwnd, &client);

    RECT infoRect = { 0, 0, client.right, INFO_HEIGHT };

    // Clear background
    FillRect(hdc, &infoRect, (HBRUSH)(COLOR_WINDOW + 1));

    char buffer[64];
    // Ve thoi gian
    RECT timeRect = infoRect;
    timeRect.right = client.right / 2;

    sprintf(buffer, "Time: %d", elapsedSeconds);

    DrawTextA(
        hdc,
        buffer,
        -1,
        &timeRect,
        DT_CENTER | DT_VCENTER | DT_SINGLELINE
    );
    // Ve so co
    RECT flagRect = infoRect;
    flagRect.left = client.right / 2;

    sprintf(buffer, "Flags: %d", FLAG_COUNT);

    DrawTextA(
        hdc,
        buffer,
        -1,
        &flagRect,
        DT_CENTER | DT_VCENTER | DT_SINGLELINE
    );
}

void drawGameOver(HWND hwnd, HDC hdc){
    RECT client;
    GetClientRect(hwnd, &client);

    FillRect(hdc, &client, (HBRUSH)(COLOR_WINDOW + 1));
    SetBkMode(hdc, TRANSPARENT);

    // Title
    HFONT hFont = CreateFont(
        40, 0, 0, 0, FW_BOLD,
        FALSE, FALSE, FALSE,
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS,
        "Arial"
    );

    HFONT oldFont = (HFONT)SelectObject(hdc, hFont);
    SetTextColor(hdc, RGB(200, 0, 0));

    DrawTextA(
        hdc,
        "GAME OVER",
        -1,
        &client,
        DT_CENTER | DT_TOP
    );

    SelectObject(hdc, oldFont);
    DeleteObject(hFont);

    // Buttons
    int btnW = 200, btnH = 40;
    int cx = (client.right - btnW) / 2;

    btnRestart = { cx, 150, cx + btnW, 190 };
    btnMenu    = { cx, 210, cx + btnW, 250 };

    Rectangle(hdc, btnRestart.left, btnRestart.top, btnRestart.right, btnRestart.bottom);
    DrawTextA(hdc, "RESTART", -1, &btnRestart, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    Rectangle(hdc, btnMenu.left, btnMenu.top, btnMenu.right, btnMenu.bottom);
    DrawTextA(hdc, "MENU", -1, &btnMenu, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void drawWin(HWND hwnd, HDC hdc){
    RECT client;
    GetClientRect(hwnd, &client);

    FillRect(hdc, &client, (HBRUSH)(COLOR_WINDOW + 1));
    SetBkMode(hdc, TRANSPARENT);

    // Title
    HFONT hFont = CreateFont(
        40, 0, 0, 0, FW_BOLD,
        FALSE, FALSE, FALSE,
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS,
        "Arial"
    );

    HFONT oldFont = (HFONT)SelectObject(hdc, hFont);
    SetTextColor(hdc, RGB(200, 0, 0));

    DrawTextA(
        hdc,
        "Victory!",
        -1,
        &client,
        DT_CENTER | DT_TOP
    );

    SelectObject(hdc, oldFont);
    DeleteObject(hFont);

    // Buttons
    int btnW = 200, btnH = 40;
    int cx = (client.right - btnW) / 2;

    btnRestart = { cx, 150, cx + btnW, 190 };
    btnMenu    = { cx, 210, cx + btnW, 250 };

    Rectangle(hdc, btnRestart.left, btnRestart.top, btnRestart.right, btnRestart.bottom);
    DrawTextA(hdc, "RESTART", -1, &btnRestart, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    Rectangle(hdc, btnMenu.left, btnMenu.top, btnMenu.right, btnMenu.bottom);
    DrawTextA(hdc, "MENU", -1, &btnMenu, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
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
        switch (gameState) {
            case STATE_MENU:
                drawMenu(hwnd, hdc);
                break;
            case STATE_PLAYING:
                drawBoard(hdc);
                drawInfo(hwnd, hdc);
                break;
            case STATE_GAMEOVER:
                drawGameOver(hwnd, hdc);
                break;
            case STATE_WIN:
                drawWin(hwnd, hdc);
                break;
        }

        // Kết thúc vẽ
        EndPaint(hwnd, &ps);
        return 0;
    }
    // case xu ly timer
    case WM_TIMER:
        // Cập nhật thời gian chơi
        if (gameState == STATE_PLAYING) {
            elapsedSeconds++;
            InvalidateRect(hwnd, NULL, TRUE);
        }
    return 0;

        // Click chuot trai - mo o
    case WM_LBUTTONDOWN:
    {
        switch (gameState)
        {
            case STATE_MENU:
            {
                POINT p = { LOWORD(lParam), HIWORD(lParam) };
                if (PtInRect(&btnEasy, p)) {
                    setDifficulty("EASY", hwnd);
                    InvalidateRect(hwnd, NULL, TRUE);
                }
                else if (PtInRect(&btnMedium, p)) {
                    setDifficulty("MEDIUM", hwnd);
                    InvalidateRect(hwnd, NULL, TRUE);
                }
                else if (PtInRect(&btnHard, p)) {
                    setDifficulty("HARD", hwnd);
                    InvalidateRect(hwnd, NULL, TRUE);
                }
                break;
            }
            case STATE_PLAYING:
            {
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
                break;
            }
            case STATE_GAMEOVER:
            {
                POINT p = { LOWORD(lParam), HIWORD(lParam) };
                if (PtInRect(&btnRestart, p)) {
                    gameInit();
                    gameState = STATE_PLAYING;
                    InvalidateRect(hwnd, NULL, TRUE);
                }
                else if (PtInRect(&btnMenu, p)) {
                    gameState = STATE_MENU;
                    InvalidateRect(hwnd, NULL, TRUE);
                }
                break;
            }
            case STATE_WIN:
            {
                POINT p = { LOWORD(lParam), HIWORD(lParam) };
                if (PtInRect(&btnRestart, p)) {
                    gameInit();
                    gameState = STATE_PLAYING;
                    InvalidateRect(hwnd, NULL, TRUE);
                }
                else if (PtInRect(&btnMenu, p)) {
                    gameState = STATE_MENU;
                    InvalidateRect(hwnd, NULL, TRUE);
                }
                break;
            }   
            default:
                break;
        }
        break;
    }

    // Click chuot phai - cam co
    case WM_RBUTTONDOWN:
    {
        if (gameState != STATE_PLAYING) return 0;

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
    gameState = STATE_MENU;
    WINDOW_WIDTH = 400;
    WINDOW_HEIGHT = 350;

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
    // mau nen cua window
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
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

    SetTimer(hwnd, 1, 1000, NULL);
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