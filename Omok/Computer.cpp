#include "Computer.h"

Computer::Computer()
{
}

Computer::~Computer()
{
}

void Computer::MakeMove()
{
    if (m_board->Access(9, 9) == Square::EMPTY) {
        m_board->UpdateSquare(9, 9, Square::BLACK);
        return;
    }
    bool moved = false;
    SearchForSeries();

    int priorities[NUMBEROFELEMENTS];
    m_array.GetHighPriority(priorities);

    int highestPriority = 0;
    int highestPriorityIndex = 0;

    int row = 0;
    int col = 0;

    // in case comp can win
    for (int i = 0; i < NUMBEROFELEMENTS; ++i) {
        if (priorities[i] == 5 || priorities[i] == 4 && m_board->Access(m_array.Get(i).row, m_array.Get(i).col) == Square::BLACK) {
            switch (m_array.Get(i).direction) {
            case Array::RIGHT:
                if (m_array.Get(i).col == 15) {
                    moved = m_board->UpdateSquare(m_array.Get(i).row, m_array.Get(i).col - 1, Square::BLACK);
                }
                else if (m_board->Access(m_array.Get(i).row, m_array.Get(i).col + 4) == Square::EMPTY) {
                    moved = m_board->UpdateSquare(m_array.Get(i).row, m_array.Get(i).col + 4, Square::BLACK);
                }
                else {
                    moved = m_board->UpdateSquare(m_array.Get(i).row, m_array.Get(i).col - 1, Square::BLACK);
                }
                row = m_array.Get(i).row;
                col = m_array.Get(i).col + 4;
                if (moved) { return; }
                break;

            case Array::DOWN:
                if (m_array.Get(i).col == 18) {
                    moved = m_board->UpdateSquare(m_array.Get(i).row + 4, m_array.Get(i).col, Square::BLACK);
                }
                else if (m_board->Access(m_array.Get(i).row + 4, m_array.Get(i).col) == Square::EMPTY) {
                    moved = m_board->UpdateSquare(m_array.Get(i).row + 4, m_array.Get(i).col, Square::BLACK);
                }
                else {
                    moved = m_board->UpdateSquare(m_array.Get(i).row - 1, m_array.Get(i).col, Square::BLACK);
                }
                row = m_array.Get(i).row;
                col = m_array.Get(i).col + 4;
                if (moved) { return; }
                break;
            case Array::LEFTDIAGONAL:
                if (m_board->Access(m_array.Get(i).row + 4, m_array.Get(i).col - 4) == Square::EMPTY) {
                    moved = m_board->UpdateSquare(m_array.Get(i).row + 4, m_array.Get(i).col - 4, Square::BLACK);
                }
                else {
                    moved = m_board->UpdateSquare(m_array.Get(i).row - 1, m_array.Get(i).col + 1, Square::BLACK);
                }
                row = m_array.Get(i).row;
                col = m_array.Get(i).col + 4;
                if (moved) { return; }
                break;
            case Array::RIGHTDIAGONAL:
                if (m_board->Access(m_array.Get(i).row + 4, m_array.Get(i).col + 4) == Square::EMPTY) {
                    moved = m_board->UpdateSquare(m_array.Get(i).row + 4, m_array.Get(i).col + 4, Square::BLACK);
                }
                else {
                    moved = m_board->UpdateSquare(m_array.Get(i).row - 1, m_array.Get(i).col - 1, Square::BLACK);
                }
                row = m_array.Get(i).row;
                col = m_array.Get(i).col + 4;
                if (moved) { return; }
                break;
            }
        }
        if (priorities[i] > highestPriority) {
            highestPriority = priorities[i];
            highestPriorityIndex = i;
        }
    }

    // for all other emergencies
    for (int i = 0; i < NUMBEROFELEMENTS; ++i) {
        if (priorities[i] == 5 || priorities[i] == 4) {
            switch (m_array.Get(i).direction) {
            case Array::RIGHT:
                if (m_board->Access(m_array.Get(i).row, m_array.Get(i).col + 4) == Square::EMPTY) {
                    moved = m_board->UpdateSquare(m_array.Get(i).row, m_array.Get(i).col + 4, Square::BLACK);
                }
                else {
                    moved = m_board->UpdateSquare(m_array.Get(i).row, m_array.Get(i).col - 1, Square::BLACK);
                }
                row = m_array.Get(i).row;
                col = m_array.Get(i).col + 4;
                if (moved) { return; }
                break;

            case Array::DOWN:
                if (m_board->Access(m_array.Get(i).row + 4, m_array.Get(i).col) == Square::EMPTY) {
                    moved = m_board->UpdateSquare(m_array.Get(i).row + 4, m_array.Get(i).col, Square::BLACK);
                }
                else {
                    moved = m_board->UpdateSquare(m_array.Get(i).row - 1, m_array.Get(i).col, Square::BLACK);
                }
                row = m_array.Get(i).row;
                col = m_array.Get(i).col + 4;
                if (moved) { return; }
                break;
            case Array::LEFTDIAGONAL:
                if (m_board->Access(m_array.Get(i).row + 4, m_array.Get(i).col - 4) == Square::EMPTY) {
                    moved = m_board->UpdateSquare(m_array.Get(i).row + 4, m_array.Get(i).col - 4, Square::BLACK);
                }
                else {
                    moved = m_board->UpdateSquare(m_array.Get(i).row - 1, m_array.Get(i).col + 1, Square::BLACK);
                }
                row = m_array.Get(i).row;
                col = m_array.Get(i).col + 4;
                if (moved) { return; }
                break;
            case Array::RIGHTDIAGONAL:
                if (m_board->Access(m_array.Get(i).row + 4, m_array.Get(i).col + 4) == Square::EMPTY) {
                    moved = m_board->UpdateSquare(m_array.Get(i).row + 4, m_array.Get(i).col + 4, Square::BLACK);
                }
                else {
                    moved = m_board->UpdateSquare(m_array.Get(i).row - 1, m_array.Get(i).col - 1, Square::BLACK);
                }
                row = m_array.Get(i).row;
                col = m_array.Get(i).col + 4;
                if (moved) { return; }
                break;
            }
        }
        if (priorities[i] > highestPriority) {
            highestPriority = priorities[i];
            highestPriorityIndex = i;
        }
    }


    if (!moved) {
        bool tricks = SearchForTricks();
        if (tricks) { return; }

        if (highestPriority > 0) {
            Array::PieceInfo neededPiece = m_array.Get(highestPriorityIndex);

            switch (highestPriority) {
            case 5:
                switch (neededPiece.direction) {
                case Array::RIGHT:
                    moved = m_board->UpdateSquare(neededPiece.row, neededPiece.col + 4, Square::BLACK);
                    row = neededPiece.row;
                    col = neededPiece.col + 4;
                    break;

                case Array::DOWN:
                    moved = m_board->UpdateSquare(neededPiece.row + 4, neededPiece.col, Square::BLACK);
                    row = neededPiece.row;
                    col = neededPiece.col + 4;
                    break;
                case Array::LEFTDIAGONAL:
                    moved = m_board->UpdateSquare(neededPiece.row + 4, neededPiece.col - 4, Square::BLACK);
                    row = neededPiece.row;
                    col = neededPiece.col + 4;
                    break;
                case Array::RIGHTDIAGONAL:
                    moved = m_board->UpdateSquare(neededPiece.row + 4, neededPiece.col + 4, Square::BLACK);
                    row = neededPiece.row;
                    col = neededPiece.col + 4;
                    break;
                }
                break;

            case 4:
                switch (neededPiece.direction) {
                case Array::RIGHT:
                    if (neededPiece.col == 0) {
                        moved = m_board->UpdateSquare(neededPiece.row, neededPiece.col + 4, Square::BLACK);
                        row = neededPiece.row;
                        col = neededPiece.col + 4;
                    }
                    else {
                        if (m_board->Access(neededPiece.row, neededPiece.col - 1) == Square::EMPTY) {
                            moved = m_board->UpdateSquare(neededPiece.row, neededPiece.col - 1, Square::BLACK);
                            row = neededPiece.row;
                            col = neededPiece.col + 4;
                        }
                        else {
                            moved = m_board->UpdateSquare(neededPiece.row, neededPiece.col + 4, Square::BLACK);
                            row = neededPiece.row;
                            col = neededPiece.col + 4;
                        }
                    }
                    break;

                case Array::DOWN:
                    if (neededPiece.row == 0) {
                        moved = m_board->UpdateSquare(neededPiece.row + 4, neededPiece.col, Square::BLACK);
                        row = neededPiece.row;
                        col = neededPiece.col + 4;
                    }
                    else {
                        if (m_board->Access(neededPiece.row - 1, neededPiece.col) == Square::EMPTY) {
                            moved = m_board->UpdateSquare(neededPiece.row - 1, neededPiece.col, Square::BLACK);
                            row = neededPiece.row;
                            col = neededPiece.col + 4;
                        }
                        else {
                            moved = m_board->UpdateSquare(neededPiece.row + 4, neededPiece.col, Square::BLACK);
                            row = neededPiece.row;
                            col = neededPiece.col + 4;
                        }
                    }
                    break;
                case Array::LEFTDIAGONAL:
                    if (neededPiece.row == 0) {
                        moved = m_board->UpdateSquare(neededPiece.row + 4, neededPiece.col - 4, Square::BLACK);
                        row = neededPiece.row;
                        col = neededPiece.col + 4;
                    }
                    else {
                        if (m_board->Access(neededPiece.row - 1, neededPiece.col + 1) == Square::EMPTY) {
                            moved = m_board->UpdateSquare(neededPiece.row - 1, neededPiece.col + 1, Square::BLACK);
                            row = neededPiece.row;
                            col = neededPiece.col + 4;
                        }
                        else {
                            moved = m_board->UpdateSquare(neededPiece.row + 4, neededPiece.col - 4, Square::BLACK);
                            row = neededPiece.row;
                            col = neededPiece.col + 4;
                        }
                    }
                    break;
                case Array::RIGHTDIAGONAL:
                    if (neededPiece.row == 0) {
                        moved = m_board->UpdateSquare(neededPiece.row + 4, neededPiece.col + 4, Square::BLACK);
                        row = neededPiece.row;
                        col = neededPiece.col + 4;
                    }
                    else {
                        if (m_board->Access(neededPiece.row - 1, neededPiece.col - 1) == Square::EMPTY) {
                            moved = m_board->UpdateSquare(neededPiece.row - 1, neededPiece.col - 1, Square::BLACK);
                            row = neededPiece.row;
                            col = neededPiece.col + 4;
                        }
                        else {
                            moved = m_board->UpdateSquare(neededPiece.row + 4, neededPiece.col + 4, Square::BLACK);
                            row = neededPiece.row;
                            col = neededPiece.col + 4;
                        }
                    }
                    break;
                }
                break;

            case 3:
                switch (neededPiece.direction) {
                case Array::RIGHT:
                    moved = m_board->UpdateSquare(neededPiece.row, neededPiece.col + 3, Square::BLACK);
                    row = neededPiece.row;
                    col = neededPiece.col + 4;
                    break;

                case Array::DOWN:
                    moved = m_board->UpdateSquare(neededPiece.row + 3, neededPiece.col, Square::BLACK);
                    row = neededPiece.row;
                    col = neededPiece.col + 4;
                    break;
                case Array::LEFTDIAGONAL:
                    moved = m_board->UpdateSquare(neededPiece.row + 3, neededPiece.col - 3, Square::BLACK);
                    row = neededPiece.row;
                    col = neededPiece.col + 4;
                    break;
                case Array::RIGHTDIAGONAL:
                    moved = m_board->UpdateSquare(neededPiece.row + 3, neededPiece.col + 3, Square::BLACK);
                    row = neededPiece.row;
                    col = neededPiece.col + 4;
                    break;
                }
                break;

            case 2:
                switch (neededPiece.direction) {
                case Array::RIGHT:
                    if (neededPiece.col == 0) {
                        moved = m_board->UpdateSquare(neededPiece.row, neededPiece.col + 3, Square::BLACK);
                        row = neededPiece.row;
                        col = neededPiece.col + 4;
                    }
                    else {
                        if (m_board->Access(neededPiece.row, neededPiece.col - 1) == Square::EMPTY) {
                            moved = m_board->UpdateSquare(neededPiece.row, neededPiece.col - 1, Square::BLACK);
                            row = neededPiece.row;
                            col = neededPiece.col + 4;
                        }
                        else {
                            moved = m_board->UpdateSquare(neededPiece.row, neededPiece.col + 3, Square::BLACK);
                            row = neededPiece.row;
                            col = neededPiece.col + 4;
                        }
                    }
                    break;

                case Array::DOWN:
                    if (neededPiece.row == 0) {
                        moved = m_board->UpdateSquare(neededPiece.row + 3, neededPiece.col, Square::BLACK);
                        row = neededPiece.row;
                        col = neededPiece.col + 4;
                    }
                    else {
                        if (m_board->Access(neededPiece.row - 1, neededPiece.col) == Square::EMPTY) {
                            moved = m_board->UpdateSquare(neededPiece.row - 1, neededPiece.col, Square::BLACK);
                            row = neededPiece.row;
                            col = neededPiece.col + 4;
                        }
                        else {
                            moved = m_board->UpdateSquare(neededPiece.row + 3, neededPiece.col, Square::BLACK);
                            row = neededPiece.row;
                            col = neededPiece.col + 4;
                        }
                    }
                    break;
                case Array::LEFTDIAGONAL:
                    if (neededPiece.row == 0) {
                        moved = m_board->UpdateSquare(neededPiece.row + 3, neededPiece.col - 3, Square::BLACK);
                        row = neededPiece.row;
                        col = neededPiece.col + 4;
                    }
                    else {
                        if (m_board->Access(neededPiece.row - 1, neededPiece.col + 1) == Square::EMPTY) {
                            moved = m_board->UpdateSquare(neededPiece.row - 1, neededPiece.col + 1, Square::BLACK);
                            row = neededPiece.row;
                            col = neededPiece.col + 4;
                        }
                        else {
                            moved = m_board->UpdateSquare(neededPiece.row + 3, neededPiece.col - 3, Square::BLACK);
                            row = neededPiece.row;
                            col = neededPiece.col + 4;
                        }
                    }
                    break;
                case Array::RIGHTDIAGONAL:
                    if (neededPiece.row == 0) {
                        moved = m_board->UpdateSquare(neededPiece.row + 3, neededPiece.col + 3, Square::BLACK);
                        row = neededPiece.row;
                        col = neededPiece.col + 4;
                    }
                    else {
                        if (m_board->Access(neededPiece.row - 1, neededPiece.col - 1) == Square::EMPTY) {
                            moved = m_board->UpdateSquare(neededPiece.row - 1, neededPiece.col - 1, Square::BLACK);
                            row = neededPiece.row;
                            col = neededPiece.col + 4;
                        }
                        else {
                            moved = m_board->UpdateSquare(neededPiece.row + 3, neededPiece.col + 3, Square::BLACK);
                            row = neededPiece.row;
                            col = neededPiece.col + 4;
                        }
                    }
                    break;
                }
                break;

            case 1:
                switch (neededPiece.direction) {
                case Array::RIGHT:
                    if (neededPiece.col == 0) {
                        moved = m_board->UpdateSquare(neededPiece.row, neededPiece.col + 2, Square::BLACK);
                        row = neededPiece.row;
                        col = neededPiece.col + 4;
                    }
                    else {
                        if (m_board->Access(neededPiece.row, neededPiece.col - 1) == Square::EMPTY && m_board->Access(neededPiece.row, neededPiece.col - 2) != Square::WHITE) {
                            moved = m_board->UpdateSquare(neededPiece.row, neededPiece.col - 1, Square::BLACK);
                            row = neededPiece.row;
                            col = neededPiece.col + 4;
                        }
                        else {
                            moved = m_board->UpdateSquare(neededPiece.row, neededPiece.col + 2, Square::BLACK);
                            row = neededPiece.row;
                            col = neededPiece.col + 4;
                        }
                    }
                    break;

                case Array::DOWN:
                    if (neededPiece.row == 0) {
                        moved = m_board->UpdateSquare(neededPiece.row + 2, neededPiece.col, Square::BLACK);
                        row = neededPiece.row;
                        col = neededPiece.col + 4;
                    }
                    else {
                        if (m_board->Access(neededPiece.row - 1, neededPiece.col) == Square::EMPTY && m_board->Access(neededPiece.row - 2, neededPiece.col) != Square::WHITE) {
                            moved = m_board->UpdateSquare(neededPiece.row - 1, neededPiece.col, Square::BLACK);
                            row = neededPiece.row;
                            col = neededPiece.col + 4;
                        }
                        else {
                            moved = m_board->UpdateSquare(neededPiece.row + 2, neededPiece.col, Square::BLACK);
                            row = neededPiece.row;
                            col = neededPiece.col + 4;
                        }
                    }
                    break;
                case Array::LEFTDIAGONAL:
                    if (neededPiece.row == 0) {
                        moved = m_board->UpdateSquare(neededPiece.row + 2, neededPiece.col - 2, Square::BLACK);
                        row = neededPiece.row;
                        col = neededPiece.col + 4;
                    }
                    else {
                        if (m_board->Access(neededPiece.row - 1, neededPiece.col + 1) == Square::EMPTY && m_board->Access(neededPiece.row - 2, neededPiece.col + 2) != Square::WHITE) {
                            moved = m_board->UpdateSquare(neededPiece.row - 1, neededPiece.col + 1, Square::BLACK);
                            row = neededPiece.row;
                            col = neededPiece.col + 4;
                        }
                        else {
                            moved = m_board->UpdateSquare(neededPiece.row + 2, neededPiece.col - 2, Square::BLACK);
                            row = neededPiece.row;
                            col = neededPiece.col + 4;
                        }
                    }
                    break;
                case Array::RIGHTDIAGONAL:
                    if (neededPiece.row == 0) {
                        moved = m_board->UpdateSquare(neededPiece.row + 2, neededPiece.col + 2, Square::BLACK);
                        row = neededPiece.row;
                        col = neededPiece.col + 4;
                    }
                    else {
                        if (m_board->Access(neededPiece.row - 1, neededPiece.col - 1) == Square::EMPTY && m_board->Access(neededPiece.row - 2, neededPiece.col) != Square::WHITE) {
                            moved = m_board->UpdateSquare(neededPiece.row - 1, neededPiece.col - 1, Square::BLACK);
                            row = neededPiece.row;
                            col = neededPiece.col + 4;
                        }
                        else {
                            moved = m_board->UpdateSquare(neededPiece.row + 2, neededPiece.col + 2, Square::BLACK);
                            row = neededPiece.row;
                            col = neededPiece.col + 4;
                        }
                    }
                    break;
                }

                break;
            }
        }
        m_array.Clear();
        if (!moved) {




            for (int i = 0; i < 10; ++i) {
                if (9 + i != row) {
                    if (m_board->Access(9 + i, 9) == Square::EMPTY) {
                        m_board->UpdateSquare(9 + i, 9, Square::BLACK);
                        moved = true;
                        return;
                    }
                    if (m_board->Access(9 + i, 9 + i) == Square::EMPTY) {
                        m_board->UpdateSquare(9 + i, 9 + i, Square::BLACK);
                        moved = true;
                        return;
                    }
                    if (m_board->Access(9 + i, 9 - i) == Square::EMPTY) {
                        m_board->UpdateSquare(9 + i, 9 - i, Square::BLACK);
                        moved = true;
                        return;
                    }
                }
                if (9 + i != col) {
                    if (m_board->Access(9, 9 + i) == Square::EMPTY) {
                        m_board->UpdateSquare(9, 9 + i, Square::BLACK);
                        moved = true;
                        return;
                    }
                    if (m_board->Access(9 - i, 9) == Square::EMPTY) {
                        m_board->UpdateSquare(9 - i, 9, Square::BLACK);
                        moved = true;
                        return;
                    }
                }
            }
        }
    }
}

void Computer::Initialize(Board* board)
{
    m_board = board;
}

void Computer::SearchForSeries()
{
    m_array.Clear();
    int arrayIndex = 0;
    for (int row = 0; row < 19; ++row) {
        for (int col = 0; col < 19; ++col) {
            Square::Piece piece = m_board->Access(row, col);
            if (piece == Square::EMPTY) { continue; }
            int rightSeq = 1;
            int downSeq = 1;
            int diagLSeq = 1;
            int diagRSeq = 1;
            int rightBlockedEnds = 0;
            int downBlockedEnds = 0;
            int diagLBlockedEnds = 0;
            int diagRBlockedEnds = 0;
            bool rightValid = true;
            bool downValid = true;
            bool diagLValid = true;
            bool diagRValid = true;

            // check for the first blocked end
            
            // right
            if (col != 0) {
                if (m_board->Access(row, col - 1) == piece) {
                    rightValid = false;
                }
                else if (m_board->Access(row, col - 1) != Square::EMPTY) {
                    ++rightBlockedEnds;
                }
            }
            else { ++rightBlockedEnds; }

            // down
            if (row != 0) {
                if (m_board->Access(row - 1, col) == piece) {
                    downValid = false;
                }
                else if (m_board->Access(row - 1, col) != Square::EMPTY) {
                    ++downBlockedEnds;
                }
            }
            else { ++downBlockedEnds; }

            // diagonal left
            if (row != 0 && col != 19) {
                if (m_board->Access(row - 1, col + 1) == piece) {
                    diagLValid = false;
                }
                else if (m_board->Access(row - 1, col + 1) != Square::EMPTY) {
                    ++diagLBlockedEnds;
                }
            }
            else { ++diagLBlockedEnds; }

            // diagonal right
            if (row != 0 && col != 0) {
                if (m_board->Access(row - 1, col - 1) == piece) {
                    diagRValid = false;
                }
                else if (m_board->Access(row - 1, col - 1) != Square::EMPTY) {
                    ++diagRBlockedEnds;
                }
            }
            else { ++diagRBlockedEnds; }


            for (int i = 1; i < 6; ++i) {
                // right
                if (rightValid) {
                    if (m_board->Access(row, col + i) == piece) {
                        ++rightSeq;
                    }
                    else if (rightSeq > 1) {
                        if (m_board->Access(row, col + i) == Square::EMPTY) {
                            m_array.InputInfo(row, col, piece, rightSeq, arrayIndex, rightBlockedEnds, Array::RIGHT);
                            ++arrayIndex;
                        }
                        // one way blocked
                        else {
                            ++rightBlockedEnds;
                            m_array.InputInfo(row, col, piece, rightSeq, arrayIndex, rightBlockedEnds, Array::RIGHT);
                            ++arrayIndex;
                        }
                        rightValid = false;
                    }
                    else { rightValid = false; }
                }

                // down
                if (downValid) {
                    if (m_board->Access(row + i, col) == piece) {
                        ++downSeq;
                    }
                    else if (downSeq > 1) {
                        if (m_board->Access(row + i, col) == Square::EMPTY) {
                            m_array.InputInfo(row, col, piece, downSeq, arrayIndex, downBlockedEnds, Array::DOWN);
                            ++arrayIndex;
                            downValid = false;
                        }
                        // one way blocked
                        else {
                            ++downBlockedEnds;
                            m_array.InputInfo(row, col, piece, downSeq, arrayIndex, downBlockedEnds, Array::DOWN);
                            ++arrayIndex;
                            downValid = false;
                        }
                    }

                    else { downValid = false; }
                }

                // diagonal left
                if (diagLValid) {
                    if (m_board->Access(row + i, col - i) == piece) {
                        ++diagLSeq;
                    }
                    else if (diagLSeq > 1) {
                        if (m_board->Access(row + i, col - i) == Square::EMPTY) {
                            m_array.InputInfo(row, col, piece, diagLSeq, arrayIndex, diagLBlockedEnds, Array::LEFTDIAGONAL);
                            ++arrayIndex;
                            diagLValid = false;
                        }
                        // one way blocked
                        else {
                            ++diagLBlockedEnds;
                            m_array.InputInfo(row, col, piece, diagLSeq, arrayIndex, diagLBlockedEnds, Array::LEFTDIAGONAL);
                            ++arrayIndex;
                            diagLValid = false;
                        }
                    }

                    else { diagLValid = false; }
                }

                // diagonal right
                if (diagRValid) {
                    if (m_board->Access(row + i, col + i) == piece) {
                        ++diagRSeq;
                    }
                    else if (diagRSeq > 1) {
                        if (m_board->Access(row + i, col + i) == Square::EMPTY) {
                            m_array.InputInfo(row, col, piece, diagRSeq, arrayIndex, diagRBlockedEnds, Array::RIGHTDIAGONAL);
                            ++arrayIndex;
                            diagRValid = false;
                        }
                        // one way blocked
                        else {
                            ++diagRBlockedEnds;
                            m_array.InputInfo(row, col, piece, diagRSeq, arrayIndex, diagRBlockedEnds, Array::RIGHTDIAGONAL);
                            ++arrayIndex;
                            diagRValid = false;
                        }
                    }

                    else { diagRValid = false; }
                }
            }
        }
    }
}

Square::Piece Computer::Winner()
{
    m_array.Clear();
    SearchForSeries();
    Array::PieceInfo winner = m_array.FindFive();
    if (winner.stonesInSeries == 5) {
        return m_board->Access(winner.row, winner.col);
    }
    else {
        return Square::EMPTY;
    }
}

bool Computer::SearchForTricks()
{
    for (int row = 0; row < 19; ++row) {
        for (int col = 0; col < 19; ++col) {
            Square::Piece piece = m_board->Access(row, col);
            if (piece != Square::EMPTY) {
                if ((m_board->Access(row, col - 1) == Square::EMPTY && m_board->Access(row, col + 4) == Square::EMPTY) ||
                    (m_board->Access(row, col - 1) == piece || m_board->Access(row, col + 4) == piece)
                    ) {
                    // ** *
                    if (m_board->Access(row, col + 1) == piece && m_board->Access(row, col + 2) == Square::EMPTY && m_board->Access(row, col + 3) == piece) {
                        m_board->UpdateSquare(row, col + 2, Square::BLACK);
                        return true;
                    }

                    // * **
                    if (m_board->Access(row, col + 1) == Square::EMPTY && m_board->Access(row, col + 2) == piece && m_board->Access(row, col + 3) == piece) {
                        m_board->UpdateSquare(row, col + 1, Square::BLACK);
                        return true;
                    }
                }

                if (m_board->Access(row - 1, col) == Square::EMPTY && m_board->Access(row + 4, col) == Square::EMPTY ||
                    (m_board->Access(row - 1, col) == piece || m_board->Access(row + 4, col) == piece)
                    ) {
                    /*
                        *
                        *

                        *
                    */
                    if (m_board->Access(row + 1, col) == piece && m_board->Access(row + 2, col) == Square::EMPTY && m_board->Access(row + 3, col) == piece) {
                        m_board->UpdateSquare(row + 2, col, Square::BLACK);
                        return true;
                    }

                    /*
                        *

                        *
                        *
                    */
                    if (m_board->Access(row + 1, col) == Square::EMPTY && m_board->Access(row + 2, col) == piece && m_board->Access(row + 3, col) == piece) {
                        m_board->UpdateSquare(row + 1, col, Square::BLACK);
                        return true;
                    }
                }
                
                if (m_board->Access(row - 1, col + 1) == Square::EMPTY && m_board->Access(row + 4, col - 4) == Square::EMPTY ||
                    (m_board->Access(row - 1, col + 1) == piece || m_board->Access(row + 4, col - 4) == piece)
                    ) {
                    /*
                        *

                      *
                     *
                    */
                    if (m_board->Access(row + 1, col - 1) == Square::EMPTY && m_board->Access(row + 2, col - 2) == piece && m_board->Access(row + 3, col - 3) == piece) {
                        m_board->UpdateSquare(row + 1, col - 1, Square::BLACK);
                        return true;
                    }

                    /*
                        *
                       *

                     *
                    */
                    if (m_board->Access(row + 1, col - 1) == piece && m_board->Access(row + 2, col - 2) == Square::EMPTY && m_board->Access(row + 3, col - 3) == piece) {
                        m_board->UpdateSquare(row + 2, col - 2, Square::BLACK);
                        return true;
                    }
                }

                if (m_board->Access(row - 1, col - 1) == Square::EMPTY && m_board->Access(row + 4, col + 4) == Square::EMPTY ||
                    (m_board->Access(row - 1, col - 1) == piece || m_board->Access(row + 4, col + 4) == piece)
                    ) {
                    /*
                        *

                          *
                           *
                    */
                    if (m_board->Access(row + 1, col + 1) == Square::EMPTY && m_board->Access(row + 2, col + 2) == piece && m_board->Access(row + 3, col + 3) == piece) {
                        m_board->UpdateSquare(row + 1, col + 1, Square::BLACK);
                        return true;
                    }

                    /*
                        *
                         *

                           *
                    */
                    if (m_board->Access(row + 1, col + 1) == piece && m_board->Access(row + 2, col + 2) == Square::EMPTY && m_board->Access(row + 3, col + 3) == piece) {
                        m_board->UpdateSquare(row + 2, col + 2, Square::BLACK);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
