#include "Board.h"


Board::Board()
{
}

Board::~Board()
{
    DeleteObject(m_brush);
}

void Board::Initialize(HWND hWnd, HDC hDC, int squareLen)
{
    m_hWnd = hWnd;
    m_hDC = hDC;
    m_squareLen = squareLen;
    HBRUSH m_brush = CreateSolidBrush(RGB(187, 170, 64));
}


void Board::Paint()
{
    // clear
    HBRUSH theBrush = CreateSolidBrush(RGB(187, 170, 64));
    RECT rect;
    rect.left = 0;
    rect.right = 1000;
    rect.top = 0;
    rect.bottom = 1000;
    FillRect(m_hDC, &rect, theBrush);

    // draw grid lines
    for (int i = 1; i < 20; ++i) {
        MoveToEx(m_hDC, m_squareLen, m_squareLen * i, nullptr);
        LineTo(m_hDC, m_squareLen * 19, m_squareLen * i);
        MoveToEx(m_hDC, m_squareLen * i, m_squareLen, nullptr);
        LineTo(m_hDC, m_squareLen * i, m_squareLen * 19);
    }

    // draw pieces
    MoveList::Move lastMove = m_moveList.Retrieve();
    for (int row = 0; row < 19; ++row) {
        for (int column = 0; column < 19; ++column) {
            int x = m_squareLen * (column + 1);
            int y = m_squareLen * (row + 1);
            if (lastMove.color != Square::EMPTY && row == lastMove.row && column == lastMove.col) {
                m_board[row][column].Paint(m_hDC, x, y, (m_squareLen * 4 / 5) / 2, true);
            }
            else {
                m_board[row][column].Paint(m_hDC, x, y, (m_squareLen * 4 / 5) / 2, false);
            }
        }
    }
}

bool Board::UpdateSquare(int row, int col, Square::Piece color)
{
    if (row < 0 || col < 0) { return false; }
    if (m_board[row][col].GetPiece() != Square::EMPTY) {
        return false;
    };
    m_board[row][col].NewPiece(color);
    if (!CheckForThrees(row, col, color)) {
        m_moveList.Add(row, col, color);
        Paint();
        return true;
    }
    else {
        m_board[row][col].NewPiece(Square::EMPTY);
        if (color == Square::WHITE) {
            MessageBox(m_hWnd, L"Rule of three!!!1!111!!!1111!!", L"Nope!", MB_OK);
        }
        else {
            for (int i = 1; i < 10; ++i) {
                if (row + i < 19 && m_board[row + i][col].GetPiece() == Square::EMPTY) {
                    m_board[row + i][col].NewPiece(color);
                    if (!CheckForThrees(row + i, col, color)) {
                        m_moveList.Add(row + i, col, color);
                        Paint();
                        return true;
                    }
                    else {
                        m_board[row + i][col].NewPiece(Square::EMPTY);
                    }
                }
                if (col + i < 19 && m_board[row][col + i].GetPiece() == Square::EMPTY) {
                    m_board[row][col + i].NewPiece(color);
                    if (!CheckForThrees(row, col + i, color)) {
                        m_moveList.Add(row, col + i, color);
                        Paint();
                        return true;
                    }
                    else {
                        m_board[row][col + i].NewPiece(Square::EMPTY);
                    }
                }
            }
        }
    }
    return false;
}

void Board::WinMessage(Square::Piece winner)
{
    if (winner == Square::BLACK) {
        MessageBox(m_hWnd, L"The winner is black!", L"White submits!", MB_OK);
    }
    else if (winner == Square::WHITE) {
        MessageBox(m_hWnd, L"The winner is white!", L"Black submits!", MB_OK);
    }
}

Square::Piece Board::Access(int row, int col)
{
    if (row > 18 || col > 18) { return Square::EMPTY; }
    return m_board[row][col].GetPiece();
}

bool Board::Undo()
{
    MoveList::Move last = m_moveList.Delete();
    if (last.color == Square::EMPTY) { return false; }
    m_board[last.row][last.col].NewPiece(Square::EMPTY);

    if (last.color == Square::BLACK) {
        MoveList::Move lastB = m_moveList.Delete();
        m_board[lastB.row][lastB.col].NewPiece(Square::EMPTY);
    }
    Paint();
    bool pieceIsThere = false;
    for (int row = 0; row < 19; ++row) {
        for (int col = 0; col < 19; ++col) {
            if (m_board[row][col].GetPiece() != Square::EMPTY) {
                pieceIsThere = true;
            }
        }
    }
    if (!pieceIsThere) {
        return true; // to indicate the computer needs to make a move
    }
    else {
        return false;
    }
}

void Board::ResetBoard()
{
    for (int row = 0; row < 19; ++row) {
        for (int col = 0; col < 19; ++col) {
            m_board[row][col].NewPiece(Square::EMPTY);
        }
    }
    Paint();
}

bool Board::CheckForThrees(int row, int col, Square::Piece piece)
{
    if (piece != Square::EMPTY) {
        int possibleThrees = 0;

        // 0 deg
        if (Access(row, col - 1) != piece && Access(row, col + 1) == piece && Access(row, col + 2) == piece && Access(row, col + 3) != piece &&
            (Access(row, col - 1) == Square::EMPTY || Access(row, col + 3) == Square::EMPTY)
            ) {
            ++possibleThrees;
        }
        else if (Access(row, col - 2) != piece && Access(row, col - 1) == piece && Access(row, col + 1) == piece && Access(row, col + 2) != piece &&
            (Access(row, col - 2) == Square::EMPTY || Access(row, col + 2) == Square::EMPTY)
            ) {
            ++possibleThrees;
        }

        // 45 deg
        if (Access(row + 1, col - 1) != piece && Access(row - 1, col + 1) == piece && Access(row - 2, col + 2) == piece && Access(row - 3, col + 3) != piece &&
            (Access(row + 1, col - 1) == Square::EMPTY || Access(row - 3, col + 3) == Square::EMPTY)
            ) {
            ++possibleThrees;
        }
        else if (Access(row - 2, col + 2) != piece && Access(row - 1, col + 1) == piece && Access(row + 1, col - 1) == piece && Access(row + 2, col - 2) != piece &&
            (Access(row - 2, col + 2) == Square::EMPTY || Access(row + 2, col - 2) == Square::EMPTY)
            ) {
            ++possibleThrees;
        }

        // 90 deg
        if (Access(row + 1, col) != piece && Access(row - 1, col) == piece && Access(row - 2, col) == piece && Access(row - 3, col) != piece &&
            (Access(row + 1, col) == Square::EMPTY || Access(row - 3, col) == Square::EMPTY)
            ) {
            ++possibleThrees;
        }
        else if (Access(row - 2, col) != piece && Access(row - 1, col) == piece && Access(row + 1, col) == piece && Access(row + 2, col) != piece &&
            (Access(row - 2, col) == Square::EMPTY || Access(row + 2, col) == Square::EMPTY)
            ) {
            ++possibleThrees;
        }

        // 135 deg
        if (Access(row + 1, col + 1) != piece && Access(row - 1, col - 1) == piece && Access(row - 2, col - 2) == piece && Access(row - 3, col - 3) != piece &&
            (Access(row + 1, col + 1) == Square::EMPTY || Access(row - 3, col - 3) == Square::EMPTY)
            ) {
            ++possibleThrees;
        }
        else if (Access(row - 2, col - 2) != piece && Access(row - 1, col - 1) == piece && Access(row + 1, col + 1) == piece && Access(row + 2, col + 2) != piece &&
            (Access(row - 2, col - 2) == Square::EMPTY || Access(row + 2, col + 2) == Square::EMPTY)
            ) {
            ++possibleThrees;
        }

        // 180 deg
        if (Access(row, col + 1) != piece && Access(row, col - 1) == piece && Access(row, col - 2) == piece && Access(row, col - 3) != piece &&
            (Access(row, col + 1) == Square::EMPTY || Access(row, col - 3) == Square::EMPTY)
            ) {
            ++possibleThrees;
        }

        // 225 deg
        if (Access(row - 1, col + 1) != piece && Access(row + 1, col - 1) == piece && Access(row + 2, col - 2) == piece && Access(row + 3, col - 3) != piece &&
            (Access(row - 1, col + 1) == Square::EMPTY || Access(row + 3, col - 3) == Square::EMPTY)
            ) {
            ++possibleThrees;
        }

        // 270 deg
        if (Access(row - 1, col) != piece && Access(row + 1, col) == piece && Access(row + 2, col) == piece && Access(row + 3, col) != piece &&
            (Access(row - 1, col) == Square::EMPTY || Access(row + 3, col) == Square::EMPTY)
            ) {
            ++possibleThrees;
        }

        // 315 deg
        if (Access(row - 1, col - 1) != piece && Access(row + 1, col + 1) == piece && Access(row + 2, col + 2) == piece && Access(row + 3, col + 3) != piece &&
            (Access(row - 1, col - 1) == Square::EMPTY || Access(row + 3, col + 3) == Square::EMPTY)
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

    /*
    for (int row = 0; row < 19; ++row) {
        for (int col = 0; col < 19; ++col) {
            Square::Piece piece = Access(row, col);
            if (piece != Square::EMPTY) {
                int threes = 0;

                // 0 deg
                if (Access(row, col - 1) != piece && Access(row, col + 1) == piece && Access(row, col + 2) == piece && Access(row, col + 3) != piece &&
                    (Access(row, col - 1) == Square::EMPTY || Access(row, col + 3) == Square::EMPTY)
                    ) {
                    ++threes;
                }
                else if (Access(row, col - 2) != piece && Access(row, col - 1) == piece && Access(row, col + 1) == piece && Access(row, col + 2) != piece &&
                    (Access(row, col - 2) == Square::EMPTY || Access(row, col + 2) == Square::EMPTY)
                    ) {
                    ++threes;
                }

                // 45 deg
                if (Access(row + 1, col - 1) != piece && Access(row - 1, col + 1) == piece && Access(row - 2, col + 2) == piece && Access(row - 3, col + 3) != piece &&
                    (Access(row + 1, col - 1) == Square::EMPTY || Access(row - 3, col + 3) == Square::EMPTY)
                    ) {
                    ++threes;
                }
                else if (Access(row - 2, col + 2) != piece && Access(row - 1, col + 1) == piece && Access(row + 1, col - 1) == piece && Access(row + 2, col - 2) != piece &&
                    (Access(row - 2, col + 2) == Square::EMPTY || Access(row + 2, col - 2) == Square::EMPTY)
                    ) {
                    ++threes;
                }

                // 90 deg
                if (Access(row + 1, col) != piece && Access(row - 1, col) == piece && Access(row - 2, col) == piece && Access(row - 3, col) != piece &&
                    (Access(row + 1, col) == Square::EMPTY || Access(row - 3, col) == Square::EMPTY)
                    ) {
                    ++threes;
                }
                else if (Access(row - 2, col) != piece && Access(row - 1, col) == piece && Access(row + 1, col) == piece && Access(row + 2, col) != piece &&
                    (Access(row - 2, col) == Square::EMPTY || Access(row + 2, col) == Square::EMPTY)
                    ) {
                    ++threes;
                }

                // 135 deg
                if (Access(row + 1, col + 1) != piece && Access(row - 1, col - 1) == piece && Access(row - 2, col - 2) == piece && Access(row - 3, col - 3) != piece &&
                    (Access(row + 1, col + 1) == Square::EMPTY || Access(row - 3, col - 3) == Square::EMPTY)
                    ) {
                    ++threes;
                }
                else if (Access(row - 2, col - 2) != piece && Access(row - 1, col - 1) == piece && Access(row + 1, col + 1) == piece && Access(row + 2, col + 2) != piece &&
                    (Access(row - 2, col - 2) == Square::EMPTY || Access(row + 2, col + 2) == Square::EMPTY)
                    ) {
                    ++threes;
                }

                // 180 deg
                if (Access(row, col + 1) != piece && Access(row, col - 1) == piece && Access(row, col - 2) == piece && Access(row, col - 3) != piece &&
                    (Access(row, col + 1) == Square::EMPTY || Access(row, col - 3) == Square::EMPTY)
                    ) {
                    ++threes;
                }

                // 225 deg
                if (Access(row - 1, col + 1) != piece && Access(row + 1, col - 1) == piece && Access(row + 2, col - 2) == piece && Access(row + 3, col - 3) != piece &&
                    (Access(row - 1, col + 1) == Square::EMPTY || Access(row + 3, col - 3) == Square::EMPTY)
                    ) {
                    ++threes;
                }

                // 270 deg
                if (Access(row - 1, col) != piece && Access(row + 1, col) == piece && Access(row + 2, col) == piece && Access(row + 3, col) != piece &&
                    (Access(row - 1, col) == Square::EMPTY || Access(row + 3, col) == Square::EMPTY)
                    ) {
                    ++threes;
                }

                // 315 deg
                if (Access(row - 1, col - 1) != piece && Access(row + 1, col + 1) == piece && Access(row + 2, col + 2) == piece && Access(row + 3, col + 3) != piece &&
                    (Access(row - 1, col - 1) == Square::EMPTY || Access(row + 3, col + 3) == Square::EMPTY)
                    ) {
                    ++threes;
                }

                if (threes > 1) { return true; }
            }
        }
    }
    */
    return false;
}
