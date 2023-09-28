#pragma once

#include "framework.h"
#include "Board.h"
#include "MoveManager.h"

class Computer
{
public:
    Computer();
    ~Computer();

public:
    void MakeMove(Board& board);
    void SearchForSeries(Board& board);
    Piece Winner(Board& board);
    bool SearchForTricks(Board& board);

private:
    MoveManager m_moveManager;
};
