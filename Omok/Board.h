#pragma once

#include "CommonTypes.h"
#include "MoveList.h"

#include <functional>


using BoardIterationCallback = std::function<void(int row, int col, Piece piece)>;

class Board
{
public:
    Board();
    ~Board();

public:
    void ResetBoard();
    Piece Get(int row, int col);
    bool Set(int row, int col, Piece newPiece, bool byComputer);

    void IterateOverBoard(BoardIterationCallback&& callback) const;

    // for the rule of three
    bool CheckForThrees(int row, int col, Piece piece);

    MoveStack::Move MoveListPop();

private:
    Piece m_board[BOARD_HEIGHT][BOARD_LENGTH];

    MoveStack m_moveList;
};
