#pragma once

#include "framework.h"
#include "Square.h"
#include "MoveList.h"



// this class represents the board Omok is played on
class Board
{
private:


public:
    Board();
    ~Board();

public:
    void Initialize(HWND hWnd, HDC hDC, int squareLen, bool* myTurn, GameMode* gameMode, int* wins, int* losses);
    void Paint();
    bool UpdateSquare(int row, int col, Square::Piece color);
    void WinMessage(Square::Piece winner);
    Square::Piece Access(int row, int col);
    bool Undo();
    void ResetBoard();
    bool CheckForThrees(int row, int col, Square::Piece piece);

public:
    Square::Piece NInARow(int n);

public:
    //void OpponentMakeMove();

private:
    HWND m_hWnd;
    HDC m_hDC;
    HBRUSH m_brush;
    Square m_board[19][19]; // 2d array of squares
    int m_squareLen;
    MoveList m_moveList;
    bool* m_myTurn;
    GameMode* m_gameMode;
    int* m_wins;
    int* m_losses;
};
