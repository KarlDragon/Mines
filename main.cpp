#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace chrono;

//Khai bao UI
steady_clock::time_point startTime; //lay thoi gian thuc va luu lam moc
int totalFlags;
int usedFlags;
void initUI(int bombCount) {
    startTime = steady_clock::now(); // khi bat dau game luu lai moc thoi gian thuc
    totalFlags = bombCount;
    usedFlags = 0;
}
int getTimePlayed() {
    return duration_cast<seconds>(     //chuyen doi don vi thoi gian ra chuan don vi giay
        steady_clock::now() - startTime //lay thoi gian cua nhung moc tru moc thoi luc bat dau se khoang thoi gian choi
    ).count();         //in ra thoi gian
}
int getRemainingFlags() {
    return totalFlags - usedFlags;  // con ban dau(= so bom co trong tro choi) tru co da su dung co dc so co con lai
}
// Phan giao dien 
void displayUI() {
    system("cls"); 

    cout << "Time: " << getTimePlayed() << "s";
    cout << "\tFlags left: " << getRemainingFlags() << endl;
    cout << "--------------------------------\n";
}
void runUI() {
    int lastTime = -1; //ghi nho giay truoc do

    while (true) {
        int currentTime = getTimePlayed();

        if (currentTime != lastTime) {
            displayUI();
            lastTime = currentTime;
        }
    }
}
int main() {
    //initUI(10); //cho nay de nhap so bom
    //runUI();
    return 0;
}