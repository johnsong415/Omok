#pragma once

#include "framework.h"

// this class represents the board Omok is played on
class Square
{
public:
    enum Piece {
        EMPTY = 0,
        BLACK,
        WHITE
    };

public:
    Square();
    ~Square();

public:
    Piece GetPiece();
    void NewPiece(Piece piece);
    void Paint(HDC hDC, int x, int y, int pieceRadius, bool last);
    
private:
    Piece m_piece;
};
