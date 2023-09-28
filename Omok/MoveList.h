#pragma once

#include "framework.h"

#include <stack>


// stack of all moves
class MoveStack
{
public:
    MoveStack();
    ~MoveStack();

public:
    struct Move
    {
        int row;
        int col;
        Piece color;
    };

public:
    void Push(int row, int col, Piece color);
    Move Pop();
    Move Top();

private:
    std::stack<Move> m_moves;
};
