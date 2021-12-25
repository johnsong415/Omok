#pragma once

#include "framework.h"
#include "Square.h"
#include "Board.h"
#include "Array.h"

// this class represents the board Omok is played on
class Computer
{
private:

public:
    Computer();
    ~Computer();

public:
    void MakeMove();
    void Initialize(Board* board);
    void SearchForSeries();
    Square::Piece Winner();
    bool SearchForTricks();
    
private:
    Board* m_board;
    Array m_array;
};
