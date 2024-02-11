#include <iostream>
#include <windows.h>
using namespace std;

wstring tetromino[7];

int nFieldWidth = 12; // field width
int nFieldHeight = 18; // field height
unsigned char* pField = nullptr; // piece field which will be dynamically allocated

int nScreenWidth = 120;  // console screeen width (columns)
int nScreenHeight = 30; // console screen height (rows)

int rotate(int px, int py, int r) {
    switch (r % 4) {
    case 0: return py * 4 + px; // for 0 degrees
    case 1: return 12 + py - (px * 4); // for 90 degrees rotation
    case 2: return 15 - (py * 4) - px; // for 180 degrees rotation
    case 3: return 3 - py + (px * 4);  // for 270 degrees rotation
    }
}
int main()
{
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");   


    tetromino[1].append(L"..X.");
    tetromino[1].append(L".XX.");
    tetromino[1].append(L".X..");
    tetromino[1].append(L"....");


    tetromino[2].append(L".X..");
    tetromino[2].append(L".XX.");
    tetromino[2].append(L"..X.");
    tetromino[2].append(L"....");

    tetromino[3].append(L"....");
    tetromino[3].append(L".XX.");
    tetromino[3].append(L".XX.");
    tetromino[3].append(L"....");

    tetromino[4].append(L"..X.");
    tetromino[4].append(L".XX.");
    tetromino[4].append(L"..X.");
    tetromino[4].append(L"....");

    tetromino[5].append(L"....");
    tetromino[5].append(L".XX.");
    tetromino[5].append(L"..X.");
    tetromino[5].append(L"..X.");

    tetromino[6].append(L"....");
    tetromino[6].append(L".XX.");
    tetromino[6].append(L".X..");
    tetromino[6].append(L".X..");

    pField = new unsigned char[nFieldWidth * nFieldHeight]; // this is the play field buffer

    for (int x = 0; x < nFieldWidth; x++) {
        for (int y = 0; y < nFieldHeight; y++) {
            // the field would be a container with 9 as the border of the container and 0 as the empty space of the container
            pField[y * nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;
        }
    }

    wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
    for (int i = 0; i < nScreenWidth * nScreenHeight; i++) {
        screen[i] = L' ';
    }
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

    bool bGameOver = false;

    while (!bGameOver) {

        //GAME TIMING ================================================>

        // INPUT =====================================================>

        // GAME LOGIC ================================================>

        // RENDER OUTPUT =============================================>

        for (int x = 0; x < nFieldWidth; x++) {
            for (int y = 0; y < nFieldHeight; y++) {
                screen[(y+2) * nScreenWidth + (x+2)] = L" ABCDEFG=#"[pField[y * nFieldWidth + x]];
            }
        }

        // to display frame
        WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
    }

    std::cout << "Hello World!\n";
}
