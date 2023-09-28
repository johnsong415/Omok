#include "Board.h"

#include "Graphics.h"

Board::Board()
{
    ResetBoard();
}

Board::~Board()
{
}

void Board::ResetBoard()
{
    for (int row = 0; row < BOARD_HEIGHT; ++row) {
        for (int col = 0; col < BOARD_LENGTH; ++col) {
            m_board[row][col] = EMPTY;
        }
    }
}

Piece Board::Get(int row, int col)
{
    return m_board[row][col];
}

bool Board::Set(int row, int col, Piece newPiece, bool byComputer)
{
    if (row < 0 || col < 0) return false;

    m_board[row][col] = newPiece;

    if (!CheckForThrees(row, col, newPiece)) {
        m_moveList.Push(row, col, newPiece);
        return true;
    }
    else {
        m_board[row][col] = EMPTY;
        if (!byComputer) {
            Graphics::Get().Message(L"Rule of three!", L"Try another place");
            return false;
        }
        else {
            for (int i = 1; i < 10; ++i) {
                if (row + i < 19 && m_board[row + i][col] == EMPTY) {
                    m_board[row + i][col] = newPiece;
                    if (!CheckForThrees(row + i, col, newPiece)) {
                        m_moveList.Push(row + i, col, newPiece);
                        return true;
                    }
                    else {
                        m_board[row + i][col] = EMPTY;
                    }
                }
                if (col + i < 19 && m_board[row][col + i] == EMPTY) {
                    m_board[row][col + i] = newPiece;
                    if (!CheckForThrees(row, col + i, newPiece)) {
                        m_moveList.Push(row, col + i, newPiece);
                        return true;
                    }
                    else {
                        m_board[row][col + i] = EMPTY;
                    }
                }
            }
        }
    }
    return false;
}

void Board::IterateOverBoard(BoardIterationCallback&& callback) const
{
    for (int row = 0; row < BOARD_HEIGHT; ++row) {
        for (int col = 0; col < BOARD_LENGTH; ++col) {
            callback(row, col, m_board[row][col]);
        }
    }
}

bool Board::CheckForThrees(int row, int col, Piece piece)
{
    if (piece != EMPTY) {
        int possibleThrees = 0;

        // 0 deg
        if (Get(row, col - 1) != piece && Get(row, col + 1) == piece && Get(row, col + 2) == piece && Get(row, col + 3) != piece &&
            (Get(row, col - 1) == EMPTY || Get(row, col + 3) == EMPTY)
            ) {
            ++possibleThrees;
        }
        else if (Get(row, col - 2) != piece && Get(row, col - 1) == piece && Get(row, col + 1) == piece && Get(row, col + 2) != piece &&
            (Get(row, col - 2) == EMPTY || Get(row, col + 2) == EMPTY)
            ) {
            ++possibleThrees;
        }

        // 45 deg
        if (Get(row + 1, col - 1) != piece && Get(row - 1, col + 1) == piece && Get(row - 2, col + 2) == piece && Get(row - 3, col + 3) != piece &&
            (Get(row + 1, col - 1) == EMPTY || Get(row - 3, col + 3) == EMPTY)
            ) {
            ++possibleThrees;
        }
        else if (Get(row - 2, col + 2) != piece && Get(row - 1, col + 1) == piece && Get(row + 1, col - 1) == piece && Get(row + 2, col - 2) != piece &&
            (Get(row - 2, col + 2) == EMPTY || Get(row + 2, col - 2) == EMPTY)
            ) {
            ++possibleThrees;
        }

        // 90 deg
        if (Get(row + 1, col) != piece && Get(row - 1, col) == piece && Get(row - 2, col) == piece && Get(row - 3, col) != piece &&
            (Get(row + 1, col) == EMPTY || Get(row - 3, col) == EMPTY)
            ) {
            ++possibleThrees;
        }
        else if (Get(row - 2, col) != piece && Get(row - 1, col) == piece && Get(row + 1, col) == piece && Get(row + 2, col) != piece &&
            (Get(row - 2, col) == EMPTY || Get(row + 2, col) == EMPTY)
            ) {
            ++possibleThrees;
        }

        // 135 deg
        if (Get(row + 1, col + 1) != piece && Get(row - 1, col - 1) == piece && Get(row - 2, col - 2) == piece && Get(row - 3, col - 3) != piece &&
            (Get(row + 1, col + 1) == EMPTY || Get(row - 3, col - 3) == EMPTY)
            ) {
            ++possibleThrees;
        }
        else if (Get(row - 2, col - 2) != piece && Get(row - 1, col - 1) == piece && Get(row + 1, col + 1) == piece && Get(row + 2, col + 2) != piece &&
            (Get(row - 2, col - 2) == EMPTY || Get(row + 2, col + 2) == EMPTY)
            ) {
            ++possibleThrees;
        }

        // 180 deg
        if (Get(row, col + 1) != piece && Get(row, col - 1) == piece && Get(row, col - 2) == piece && Get(row, col - 3) != piece &&
            (Get(row, col + 1) == EMPTY || Get(row, col - 3) == EMPTY)
            ) {
            ++possibleThrees;
        }

        // 225 deg
        if (Get(row - 1, col + 1) != piece && Get(row + 1, col - 1) == piece && Get(row + 2, col - 2) == piece && Get(row + 3, col - 3) != piece &&
            (Get(row - 1, col + 1) == EMPTY || Get(row + 3, col - 3) == EMPTY)
            ) {
            ++possibleThrees;
        }

        // 270 deg
        if (Get(row - 1, col) != piece && Get(row + 1, col) == piece && Get(row + 2, col) == piece && Get(row + 3, col) != piece &&
            (Get(row - 1, col) == EMPTY || Get(row + 3, col) == EMPTY)
            ) {
            ++possibleThrees;
        }

        // 315 deg
        if (Get(row - 1, col - 1) != piece && Get(row + 1, col + 1) == piece && Get(row + 2, col + 2) == piece && Get(row + 3, col + 3) != piece &&
            (Get(row - 1, col - 1) == EMPTY || Get(row + 3, col + 3) == EMPTY)
            ) {
            ++possibleThrees;
        }

        if (possibleThrees > 1) {
            return true;
        }
        else {
            return false;
        }
        // change this to suit needs
    }
    return false;
}

MoveStack::Move Board::MoveListPop()
{
    return m_moveList.Pop();
}