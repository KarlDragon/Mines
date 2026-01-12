# Role công việc
1. Tạo bảng mìn (Bomb Generator) ( Tài ) ( branch : feature/bomb-generator )
Function: generateBombMap(rows, cols, bombCount)
Return: 2D array (rows x cols)
- Random bomb positions
- Không trùng vị trí
- Ô có bom = -1
- Ô trống = 0

2. Tính số bom lân cận ( Nhận array từ hàm tạo map rồi return lại ) ( Tài ) ( branch : feature/bomb-numbers )
   Function: calculateBombNumbers(board)
  Return: 2D array

- Với mỗi ô không phải bom
- Đếm số bom trong 8 ô xung quanh
- Ghi số bom vào ô

3. Trạng thái ô (Cell State)  ( Toán ) ( branch : feature/cell-state )
   Tạo 4 mảng 2 chiều, mỗi mảng vs tên lần lượt như bên dưới
  Mỗi ô cần có:
  - isBomb: boolean
  - value: number (0–8)
  - isRevealed: boolean
  - isFlagged: boolean
    
4. Xử lý click ô  ( An ) ( branch : feature/cell-click )
  Function: handleCellClick(row, col, clickType)
  Click trái:
  
  - Nếu ô đã mở hoặc có cờ → bỏ qua
  
  - Nếu là bom → thua game
  
  - Nếu value > 0 → mở ô
  
  - Nếu value == 0 → mở ô + mở lan các ô xung quanh (flood fill) ( gọi hàm số 5 )
  
  Click phải:
  
  - Toggle cờ
  
  - Giảm / tăng số cờ còn lại
    
5. Mở ô trống (Flood Fill)  ( Hiển ) ( branch : feature/flood-fill )
  Function: revealEmptyCells(row, col)
  - Mở ô hiện tại
  
  - Nếu value == 0:
  
      Mở toàn bộ ô xung quanh
      Gọi đệ quy hoặc BFS
  
  - Không mở ô có cờ
    
6. Điều kiện thắng/thua  ( Khôi ) ( branch : feature/win-lose )
  Thua:
    - Click vào bom
  Thắng:
    - Tất cả ô KHÔNG phải bom đã được mở
      
7. Giao diện ( UI ) ( Khôi + Toán ) ( branch : feature/ui-basic )
  Hiển thị:
  - Bảng ô click được
  - Thời gian chơi
  - Điểm số
  - Số cờ còn lại
  - Màn hình thắng / thua

8. Reset game  ( An ) ( branch : feature/reset-game )
Function: resetGame()
  - Tạo lại board
  - Reset timer
  - Reset cờ & điểm

9. Testing ( Linh + Phong ) ( branch : feature/testing )
  Đảm bảo tất cả hàm phải chạy đúng và không thiếu trường hợp ngoại lệ
