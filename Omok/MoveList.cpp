#include "MoveList.h"


MoveStack::MoveStack()
{
}

MoveStack::~MoveStack()
{
}

void MoveStack::Push(int row, int col, Piece color)
{
    Move move = { row, col, color };
    m_moves.emplace(move);
}

MoveStack::Move MoveStack::Pop()
{
    if (m_moves.empty()) {
        return {-1, -1, EMPTY};
    }
    Move lastMove = m_moves.top();
    m_moves.pop();
    return lastMove;
}

MoveStack::Move MoveStack::Top()
{
    if (m_moves.empty()) {
        return { -1, -1, EMPTY };
    }
    return m_moves.top();
}
