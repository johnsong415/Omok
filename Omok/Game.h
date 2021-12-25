#pragma once

#include "framework.h"
#include "Board.h"
#include "Computer.h"

#define BOARDLENGTH         19
#define SQUARELENGTH         50

// this class represents the board Omok is played on
class Game
{
private:

public:
    Game();
    ~Game();

public:
    void Initialize(HWND hWnd, HDC hDC);
    void Update();
    void TranslateClick(POINTS point);
    int RoundFloatToInt(double val);
    bool CheckGameOver();
    void Undo();
    void Restart();

private:
    Board m_board; // 2d array of squares
    Computer m_computer;

    bool m_gameOver = false;
};
