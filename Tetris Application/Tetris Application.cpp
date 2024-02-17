#include <iostream>
#include <windows.h>
#include <thread>
using namespace std;

wstring tetromino[7]; // string of the shapes

int nFieldWidth = 20; // field width
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

bool doesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY) {

    for (int px = 0; px < 4; px++) {
        for (int py = 0; py < 4; py++) {

            // get index into piece
            int pi = rotate(px, py, nRotation);

            // get index into field
            int fi = (nPosY + py) * nFieldWidth + (nPosX + px);

            if (nPosX + px >= 0 && nPosX + px < nFieldWidth) {
                if (nPosY + py >= 0 && nPosY + py < nFieldHeight) {
                    if (tetromino[nTetromino][pi] == L'X' && pField[fi] != 0) {
                        return false; // fails
                    }
                } 
            }
        }
    }
    return true;
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


    // Game logic goes here
    bool bGameOver = false;

    int nCurrentPiece = 0; // which is the current piece
    int nCurrentRotation = 0; // which rotation is the piece at
    int nCurrentX = nFieldWidth / 2; // the x value of the top left piece in the field, in this case it is somewhere in the middle
    int nCurrentY = 0; // the y value of the top left piece in the field - so here it would be the at the start of the field


    bool bKey[4];
    bool bRotateHold = false;
    while (!bGameOver) {

        //GAME TIMING ================================================>
        this_thread::sleep_for(50ms);

        // INPUT =====================================================>
        for (int k = 0; k < 4; k++) {                             //R  L   D   Z
            bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28Z"[k]))) != 0;
        }
        // GAME LOGIC ================================================>
        if (bKey[1]) {
            if (doesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX - 1, nCurrentY)) {
                nCurrentX = nCurrentX - 1;
            }
        }
        if (bKey[0]) {
            if (doesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX + 1, nCurrentY)) {
                nCurrentX = nCurrentX + 1;
            }
        }
        if (bKey[2]) {
            if (doesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1)) {
                nCurrentY = nCurrentY + 1;
            }
        }
        if (bKey[3]) {
            if (bRotateHold == false && doesPieceFit(nCurrentPiece, nCurrentRotation + 1, nCurrentX, nCurrentY)) {
                nCurrentRotation = nCurrentRotation + 1;
                bRotateHold = true;
            }
            else bRotateHold = false;
        }
        // RENDER OUTPUT =============================================>

        for (int x = 0; x < nFieldWidth; x++) {
            for (int y = 0; y < nFieldHeight; y++) {
                screen[(y+2) * nScreenWidth + (x+2)] = L" ABCDEFG=#"[pField[y * nFieldWidth + x]];
            }
        }

        for (int px = 0; px < 4; px++) {
            for (int py = 0; py < 4; py++) {
                if (tetromino[nCurrentPiece][rotate(px, py, nCurrentRotation)] == L'X') {
                    screen[(nCurrentY + py + 2) * nScreenWidth + (nCurrentX + px + 2)] = nCurrentPiece + 65;
                }
            }
        }

        // to display frame
        WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
    }

    std::cout << "Hello World!\n";
}
