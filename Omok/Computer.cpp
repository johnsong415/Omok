#include "Computer.h"

Computer::Computer()
{
}

Computer::~Computer()
{
}

void Computer::MakeMove(Board& board)
{
    if (board.Get(9, 9) == EMPTY) {
        board.Set(9, 9, BLACK, true);
        return;
    }

    SearchForSeries(board);

    MoveManager::Sequence mostImportant = m_moveManager.GetBestSequenceInfo();

    int highestPriority = mostImportant.priority;

    int row = 0;
    int col = 0;
    bool moved = false;

    // if comp can win
    if (mostImportant.priority == 5 || mostImportant.priority == 4 && board.Get(mostImportant.row, mostImportant.col) == BLACK) {
        switch (mostImportant.direction) {
        case MoveManager::RIGHT:
            if (mostImportant.col == 15) {
                moved = board.Set(mostImportant.row, mostImportant.col - 1, BLACK, true);
            }
            else if (board.Get(mostImportant.row, mostImportant.col + 4) == EMPTY) {
                moved = board.Set(mostImportant.row, mostImportant.col + 4, BLACK, true);
            }
            else {
                moved = board.Set(mostImportant.row, mostImportant.col - 1, BLACK, true);
            }
            row = mostImportant.row;
            col = mostImportant.col + 4;
            if (moved) { return; }
            break;

        case MoveManager::DOWN:
            if (mostImportant.col == 18) {
                moved = board.Set(mostImportant.row + 4, mostImportant.col, BLACK, true);
            }
            else if (board.Get(mostImportant.row + 4, mostImportant.col) == EMPTY) {
                moved = board.Set(mostImportant.row + 4, mostImportant.col, BLACK, true);
            }
            else {
                moved = board.Set(mostImportant.row - 1, mostImportant.col, BLACK, true);
            }
            row = mostImportant.row;
            col = mostImportant.col + 4;
            if (moved) { return; }
            break;
        case MoveManager::LEFTDIAGONAL:
            if (board.Get(mostImportant.row + 4, mostImportant.col - 4) == EMPTY) {
                moved = board.Set(mostImportant.row + 4, mostImportant.col - 4, BLACK, true);
            }
            else {
                moved = board.Set(mostImportant.row - 1, mostImportant.col + 1, BLACK, true);
            }
            row = mostImportant.row;
            col = mostImportant.col + 4;
            if (moved) { return; }
            break;
        case MoveManager::RIGHTDIAGONAL:
            if (board.Get(mostImportant.row + 4, mostImportant.col + 4) == EMPTY) {
                moved = board.Set(mostImportant.row + 4, mostImportant.col + 4, BLACK, true);
            }
            else {
                moved = board.Set(mostImportant.row - 1, mostImportant.col - 1, BLACK, true);
            }
            row = mostImportant.row;
            col = mostImportant.col + 4;
            if (moved) { return; }
            break;
        }
    }
    if (mostImportant.priority == 5 || mostImportant.priority == 4) {
        switch (mostImportant.direction) {
        case MoveManager::RIGHT:
            if (board.Get(mostImportant.row, mostImportant.col + 4) == EMPTY) {
                moved = board.Set(mostImportant.row, mostImportant.col + 4, BLACK, true);
            }
            else {
                moved = board.Set(mostImportant.row, mostImportant.col - 1, BLACK, true);
            }
            row = mostImportant.row;
            col = mostImportant.col + 4;
            if (moved) { return; }
            break;

        case MoveManager::DOWN:
            if (board.Get(mostImportant.row + 4, mostImportant.col) == EMPTY) {
                moved = board.Set(mostImportant.row + 4, mostImportant.col, BLACK, true);
            }
            else {
                moved = board.Set(mostImportant.row - 1, mostImportant.col, BLACK, true);
            }
            row = mostImportant.row;
            col = mostImportant.col + 4;
            if (moved) { return; }
            break;
        case MoveManager::LEFTDIAGONAL:
            if (board.Get(mostImportant.row + 4, mostImportant.col - 4) == EMPTY) {
                moved = board.Set(mostImportant.row + 4, mostImportant.col - 4, BLACK, true);
            }
            else {
                moved = board.Set(mostImportant.row - 1, mostImportant.col + 1, BLACK, true);
            }
            row = mostImportant.row;
            col = mostImportant.col + 4;
            if (moved) { return; }
            break;
        case MoveManager::RIGHTDIAGONAL:
            if (board.Get(mostImportant.row + 4, mostImportant.col + 4) == EMPTY) {
                moved = board.Set(mostImportant.row + 4, mostImportant.col + 4, BLACK, true);
            }
            else {
                moved = board.Set(mostImportant.row - 1, mostImportant.col - 1, BLACK, true);
            }
            row = mostImportant.row;
            col = mostImportant.col + 4;
            if (moved) { return; }
            break;
        }
    }

    if (!moved) {
        bool tricks = SearchForTricks(board);
        if (tricks) { return; }

        if (highestPriority > 0) {
            //MoveManager::SequenceInfo neededPiece = m_moveManager.Get(highestPriorityIndex);

            switch (mostImportant.priority) {
            case 5:
                switch (mostImportant.direction) {
                case MoveManager::RIGHT:
                    moved = board.Set(mostImportant.row, mostImportant.col + 4, BLACK, true);
                    row = mostImportant.row;
                    col = mostImportant.col + 4;
                    break;
                case MoveManager::DOWN:
                    moved = board.Set(mostImportant.row + 4, mostImportant.col, BLACK, true);
                    row = mostImportant.row;
                    col = mostImportant.col + 4;
                    break;
                case MoveManager::LEFTDIAGONAL:
                    moved = board.Set(mostImportant.row + 4, mostImportant.col - 4, BLACK, true);
                    row = mostImportant.row;
                    col = mostImportant.col + 4;
                    break;
                case MoveManager::RIGHTDIAGONAL:
                    moved = board.Set(mostImportant.row + 4, mostImportant.col + 4, BLACK, true);
                    row = mostImportant.row;
                    col = mostImportant.col + 4;
                    break;
                }
                break;

            case 4:
                switch (mostImportant.direction) {
                case MoveManager::RIGHT:
                    if (mostImportant.col == 0) {
                        moved = board.Set(mostImportant.row, mostImportant.col + 4, BLACK, true);
                        row = mostImportant.row;
                        col = mostImportant.col + 4;
                    }
                    else {
                        if (board.Get(mostImportant.row, mostImportant.col - 1) == EMPTY) {
                            moved = board.Set(mostImportant.row, mostImportant.col - 1, BLACK, true);
                            row = mostImportant.row;
                            col = mostImportant.col + 4;
                        }
                        else {
                            moved = board.Set(mostImportant.row, mostImportant.col + 4, BLACK, true);
                            row = mostImportant.row;
                            col = mostImportant.col + 4;
                        }
                    }
                    break;

                case MoveManager::DOWN:
                    if (mostImportant.row == 0) {
                        moved = board.Set(mostImportant.row + 4, mostImportant.col, BLACK, true);
                        row = mostImportant.row;
                        col = mostImportant.col + 4;
                    }
                    else {
                        if (board.Get(mostImportant.row - 1, mostImportant.col) == EMPTY) {
                            moved = board.Set(mostImportant.row - 1, mostImportant.col, BLACK, true);
                            row = mostImportant.row;
                            col = mostImportant.col + 4;
                        }
                        else {
                            moved = board.Set(mostImportant.row + 4, mostImportant.col, BLACK, true);
                            row = mostImportant.row;
                            col = mostImportant.col + 4;
                        }
                    }
                    break;
                case MoveManager::LEFTDIAGONAL:
                    if (mostImportant.row == 0) {
                        moved = board.Set(mostImportant.row + 4, mostImportant.col - 4, BLACK, true);
                        row = mostImportant.row;
                        col = mostImportant.col + 4;
                    }
                    else {
                        if (board.Get(mostImportant.row - 1, mostImportant.col + 1) == EMPTY) {
                            moved = board.Set(mostImportant.row - 1, mostImportant.col + 1, BLACK, true);
                            row = mostImportant.row;
                            col = mostImportant.col + 4;
                        }
                        else {
                            moved = board.Set(mostImportant.row + 4, mostImportant.col - 4, BLACK, true);
                            row = mostImportant.row;
                            col = mostImportant.col + 4;
                        }
                    }
                    break;
                case MoveManager::RIGHTDIAGONAL:
                    if (mostImportant.row == 0) {
                        moved = board.Set(mostImportant.row + 4, mostImportant.col + 4, BLACK, true);
                        row = mostImportant.row;
                        col = mostImportant.col + 4;
                    }
                    else {
                        if (board.Get(mostImportant.row - 1, mostImportant.col - 1) == EMPTY) {
                            moved = board.Set(mostImportant.row - 1, mostImportant.col - 1, BLACK, true);
                            row = mostImportant.row;
                            col = mostImportant.col + 4;
                        }
                        else {
                            moved = board.Set(mostImportant.row + 4, mostImportant.col + 4, BLACK, true);
                            row = mostImportant.row;
                            col = mostImportant.col + 4;
                        }
                    }
                    break;
                }
                break;

            case 3:
                switch (mostImportant.direction) {
                case MoveManager::RIGHT:
                    moved = board.Set(mostImportant.row, mostImportant.col + 3, BLACK, true);
                    row = mostImportant.row;
                    col = mostImportant.col + 4;
                    break;

                case MoveManager::DOWN:
                    moved = board.Set(mostImportant.row + 3, mostImportant.col, BLACK, true);
                    row = mostImportant.row;
                    col = mostImportant.col + 4;
                    break;
                case MoveManager::LEFTDIAGONAL:
                    moved = board.Set(mostImportant.row + 3, mostImportant.col - 3, BLACK, true);
                    row = mostImportant.row;
                    col = mostImportant.col + 4;
                    break;
                case MoveManager::RIGHTDIAGONAL:
                    moved = board.Set(mostImportant.row + 3, mostImportant.col + 3, BLACK, true);
                    row = mostImportant.row;
                    col = mostImportant.col + 4;
                    break;
                }
                break;

            case 2:
                switch (mostImportant.direction) {
                case MoveManager::RIGHT:
                    if (mostImportant.col == 0) {
                        moved = board.Set(mostImportant.row, mostImportant.col + 3, BLACK, true);
                        row = mostImportant.row;
                        col = mostImportant.col + 4;
                    }
                    else {
                        if (board.Get(mostImportant.row, mostImportant.col - 1) == EMPTY) {
                            moved = board.Set(mostImportant.row, mostImportant.col - 1, BLACK, true);
                            row = mostImportant.row;
                            col = mostImportant.col + 4;
                        }
                        else {
                            moved = board.Set(mostImportant.row, mostImportant.col + 3, BLACK, true);
                            row = mostImportant.row;
                            col = mostImportant.col + 4;
                        }
                    }
                    break;

                case MoveManager::DOWN:
                    if (mostImportant.row == 0) {
                        moved = board.Set(mostImportant.row + 3, mostImportant.col, BLACK, true);
                        row = mostImportant.row;
                        col = mostImportant.col + 4;
                    }
                    else {
                        if (board.Get(mostImportant.row - 1, mostImportant.col) == EMPTY) {
                            moved = board.Set(mostImportant.row - 1, mostImportant.col, BLACK, true);
                            row = mostImportant.row;
                            col = mostImportant.col + 4;
                        }
                        else {
                            moved = board.Set(mostImportant.row + 3, mostImportant.col, BLACK, true);
                            row = mostImportant.row;
                            col = mostImportant.col + 4;
                        }
                    }
                    break;
                case MoveManager::LEFTDIAGONAL:
                    if (mostImportant.row == 0) {
                        moved = board.Set(mostImportant.row + 3, mostImportant.col - 3, BLACK, true);
                        row = mostImportant.row;
                        col = mostImportant.col + 4;
                    }
                    else {
                        if (board.Get(mostImportant.row - 1, mostImportant.col + 1) == EMPTY) {
                            moved = board.Set(mostImportant.row - 1, mostImportant.col + 1, BLACK, true);
                            row = mostImportant.row;
                            col = mostImportant.col + 4;
                        }
                        else {
                            moved = board.Set(mostImportant.row + 3, mostImportant.col - 3, BLACK, true);
                            row = mostImportant.row;
                            col = mostImportant.col + 4;
                        }
                    }
                    break;
                case MoveManager::RIGHTDIAGONAL:
                    if (mostImportant.row == 0) {
                        moved = board.Set(mostImportant.row + 3, mostImportant.col + 3, BLACK, true);
                        row = mostImportant.row;
                        col = mostImportant.col + 4;
                    }
                    else {
                        if (board.Get(mostImportant.row - 1, mostImportant.col - 1) == EMPTY) {
                            moved = board.Set(mostImportant.row - 1, mostImportant.col - 1, BLACK, true);
                            row = mostImportant.row;
                            col = mostImportant.col + 4;
                        }
                        else {
                            moved = board.Set(mostImportant.row + 3, mostImportant.col + 3, BLACK, true);
                            row = mostImportant.row;
                            col = mostImportant.col + 4;
                        }
                    }
                    break;
                }
                break;

            case 1:
                switch (mostImportant.direction) {
                case MoveManager::RIGHT:
                    if (mostImportant.col == 0) {
                        moved = board.Set(mostImportant.row, mostImportant.col + 2, BLACK, true);
                        row = mostImportant.row;
                        col = mostImportant.col + 4;
                    }
                    else {
                        if (board.Get(mostImportant.row, mostImportant.col - 1) == EMPTY && board.Get(mostImportant.row, mostImportant.col - 2) != WHITE) {
                            moved = board.Set(mostImportant.row, mostImportant.col - 1, BLACK, true);
                            row = mostImportant.row;
                            col = mostImportant.col + 4;
                        }
                        else {
                            moved = board.Set(mostImportant.row, mostImportant.col + 2, BLACK, true);
                            row = mostImportant.row;
                            col = mostImportant.col + 4;
                        }
                    }
                    break;

                case MoveManager::DOWN:
                    if (mostImportant.row == 0) {
                        moved = board.Set(mostImportant.row + 2, mostImportant.col, BLACK, true);
                        row = mostImportant.row;
                        col = mostImportant.col + 4;
                    }
                    else {
                        if (board.Get(mostImportant.row - 1, mostImportant.col) == EMPTY && board.Get(mostImportant.row - 2, mostImportant.col) != WHITE) {
                            moved = board.Set(mostImportant.row - 1, mostImportant.col, BLACK, true);
                            row = mostImportant.row;
                            col = mostImportant.col + 4;
                        }
                        else {
                            moved = board.Set(mostImportant.row + 2, mostImportant.col, BLACK, true);
                            row = mostImportant.row;
                            col = mostImportant.col + 4;
                        }
                    }
                    break;
                case MoveManager::LEFTDIAGONAL:
                    if (mostImportant.row == 0) {
                        moved = board.Set(mostImportant.row + 2, mostImportant.col - 2, BLACK, true);
                        row = mostImportant.row;
                        col = mostImportant.col + 4;
                    }
                    else {
                        if (board.Get(mostImportant.row - 1, mostImportant.col + 1) == EMPTY && board.Get(mostImportant.row - 2, mostImportant.col + 2) != WHITE) {
                            moved = board.Set(mostImportant.row - 1, mostImportant.col + 1, BLACK, true);
                            row = mostImportant.row;
                            col = mostImportant.col + 4;
                        }
                        else {
                            moved = board.Set(mostImportant.row + 2, mostImportant.col - 2, BLACK, true);
                            row = mostImportant.row;
                            col = mostImportant.col + 4;
                        }
                    }
                    break;
                case MoveManager::RIGHTDIAGONAL:
                    if (mostImportant.row == 0) {
                        moved = board.Set(mostImportant.row + 2, mostImportant.col + 2, BLACK, true);
                        row = mostImportant.row;
                        col = mostImportant.col + 4;
                    }
                    else {
                        if (board.Get(mostImportant.row - 1, mostImportant.col - 1) == EMPTY && board.Get(mostImportant.row - 2, mostImportant.col) != WHITE) {
                            moved = board.Set(mostImportant.row - 1, mostImportant.col - 1, BLACK, true);
                            row = mostImportant.row;
                            col = mostImportant.col + 4;
                        }
                        else {
                            moved = board.Set(mostImportant.row + 2, mostImportant.col + 2, BLACK, true);
                            row = mostImportant.row;
                            col = mostImportant.col + 4;
                        }
                    }
                    break;
                }

                break;
            }
        }

        m_moveManager.Clear();

        if (!moved) {
            for (int i = 0; i < 10; ++i) {
                if (9 + i != row) {
                    if (board.Get(9 + i, 9) == EMPTY) {
                        board.Set(9 + i, 9, BLACK, true);
                        moved = true;
                        return;
                    }
                    if (board.Get(9 + i, 9 + i) == EMPTY) {
                        board.Set(9 + i, 9 + i, BLACK, true);
                        moved = true;
                        return;
                    }
                    if (board.Get(9 + i, 9 - i) == EMPTY) {
                        board.Set(9 + i, 9 - i, BLACK, true);
                        moved = true;
                        return;
                    }
                }
                if (9 + i != col) {
                    if (board.Get(9, 9 + i) == EMPTY) {
                        board.Set(9, 9 + i, BLACK, true);
                        moved = true;
                        return;
                    }
                    if (board.Get(9 - i, 9) == EMPTY) {
                        board.Set(9 - i, 9, BLACK, true);
                        moved = true;
                        return;
                    }
                }
            }
        }
    }
}

void Computer::SearchForSeries(Board& board)
{
    m_moveManager.Clear();
    int arrayIndex = 0;
    for (int row = 0; row < 19; ++row) {
        for (int col = 0; col < 19; ++col) {
            Piece piece = board.Get(row, col);
            if (piece == EMPTY) { continue; }
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
                if (board.Get(row, col - 1) == piece) {
                    rightValid = false;
                }
                else if (board.Get(row, col - 1) != EMPTY) {
                    ++rightBlockedEnds;
                }
            }
            else {
                ++rightBlockedEnds;
            }

            // down
            if (row != 0) {
                if (board.Get(row - 1, col) == piece) {
                    downValid = false;
                }
                else if (board.Get(row - 1, col) != EMPTY) {
                    ++downBlockedEnds;
                }
            }
            else {
                ++downBlockedEnds;
            }

            // diagonal left
            if (row != 0 && col != 19) {
                if (board.Get(row - 1, col + 1) == piece) {
                    diagLValid = false;
                }
                else if (board.Get(row - 1, col + 1) != EMPTY) {
                    ++diagLBlockedEnds;
                }
            }
            else {
                ++diagLBlockedEnds;
            }

            // diagonal right
            if (row != 0 && col != 0) {
                if (board.Get(row - 1, col - 1) == piece) {
                    diagRValid = false;
                }
                else if (board.Get(row - 1, col - 1) != EMPTY) {
                    ++diagRBlockedEnds;
                }
            }
            else {
                ++diagRBlockedEnds;
            }


            for (int i = 1; i < 6; ++i) {
                // right
                if (rightValid) {
                    if (board.Get(row, col + i) == piece) {
                        ++rightSeq;
                    }
                    else if (rightSeq > 1) {
                        if (board.Get(row, col + i) == EMPTY) {
                            m_moveManager.AddSequence(row, col, piece, rightSeq, arrayIndex, rightBlockedEnds, MoveManager::RIGHT);
                            ++arrayIndex;
                        }
                        // one way blocked
                        else {
                            ++rightBlockedEnds;
                            m_moveManager.AddSequence(row, col, piece, rightSeq, arrayIndex, rightBlockedEnds, MoveManager::RIGHT);
                            ++arrayIndex;
                        }
                        rightValid = false;
                    }
                    else {
                        rightValid = false;
                    }
                }

                // down
                if (downValid) {
                    if (board.Get(row + i, col) == piece) {
                        ++downSeq;
                    }
                    else if (downSeq > 1) {
                        if (board.Get(row + i, col) == EMPTY) {
                            m_moveManager.AddSequence(row, col, piece, downSeq, arrayIndex, downBlockedEnds, MoveManager::DOWN);
                            ++arrayIndex;
                            downValid = false;
                        }
                        // one way blocked
                        else {
                            ++downBlockedEnds;
                            m_moveManager.AddSequence(row, col, piece, downSeq, arrayIndex, downBlockedEnds, MoveManager::DOWN);
                            ++arrayIndex;
                            downValid = false;
                        }
                    }
                    else {
                        downValid = false;
                    }
                }

                // diagonal left
                if (diagLValid) {
                    if (board.Get(row + i, col - i) == piece) {
                        ++diagLSeq;
                    }
                    else if (diagLSeq > 1) {
                        if (board.Get(row + i, col - i) == EMPTY) {
                            m_moveManager.AddSequence(row, col, piece, diagLSeq, arrayIndex, diagLBlockedEnds, MoveManager::LEFTDIAGONAL);
                            ++arrayIndex;
                            diagLValid = false;
                        }
                        // one way blocked
                        else {
                            ++diagLBlockedEnds;
                            m_moveManager.AddSequence(row, col, piece, diagLSeq, arrayIndex, diagLBlockedEnds, MoveManager::LEFTDIAGONAL);
                            ++arrayIndex;
                            diagLValid = false;
                        }
                    }
                    else {
                        diagLValid = false;
                    }
                }

                // diagonal right
                if (diagRValid) {
                    if (board.Get(row + i, col + i) == piece) {
                        ++diagRSeq;
                    }
                    else if (diagRSeq > 1) {
                        if (board.Get(row + i, col + i) == EMPTY) {
                            m_moveManager.AddSequence(row, col, piece, diagRSeq, arrayIndex, diagRBlockedEnds, MoveManager::RIGHTDIAGONAL);
                            ++arrayIndex;
                            diagRValid = false;
                        }
                        // one way blocked
                        else {
                            ++diagRBlockedEnds;
                            m_moveManager.AddSequence(row, col, piece, diagRSeq, arrayIndex, diagRBlockedEnds, MoveManager::RIGHTDIAGONAL);
                            ++arrayIndex;
                            diagRValid = false;
                        }
                    }
                    else {
                        diagRValid = false;
                    }
                }
            }
        }
    }
}

Piece Computer::Winner(Board& board)
{
    m_moveManager.Clear();
    SearchForSeries(board);
    MoveManager::Sequence winner = m_moveManager.GetBestSequenceInfo();
    if (winner.stonesInSeries == 5) {
        return board.Get(winner.row, winner.col);
    }
    else {
        return EMPTY;
    }
}

bool Computer::SearchForTricks(Board& board)
{
    for (int row = 0; row < 19; ++row) {
        for (int col = 0; col < 19; ++col) {
            Piece piece = board.Get(row, col);
            if (piece != EMPTY) {
                if ((board.Get(row, col - 1) == EMPTY && board.Get(row, col + 4) == EMPTY) ||
                    (board.Get(row, col - 1) == piece || board.Get(row, col + 4) == piece)
                    ) {
                    // ** *
                    if (board.Get(row, col + 1) == piece && board.Get(row, col + 2) == EMPTY && board.Get(row, col + 3) == piece) {
                        board.Set(row, col + 2, BLACK, true);
                        return true;
                    }

                    // * **
                    if (board.Get(row, col + 1) == EMPTY && board.Get(row, col + 2) == piece && board.Get(row, col + 3) == piece) {
                        board.Set(row, col + 1, BLACK, true);
                        return true;
                    }
                }

                if (board.Get(row - 1, col) == EMPTY && board.Get(row + 4, col) == EMPTY ||
                    (board.Get(row - 1, col) == piece || board.Get(row + 4, col) == piece)
                    ) {
                    /*
                        *
                        *

                        *
                    */
                    if (board.Get(row + 1, col) == piece && board.Get(row + 2, col) == EMPTY && board.Get(row + 3, col) == piece) {
                        board.Set(row + 2, col, BLACK, true);
                        return true;
                    }

                    /*
                        *

                        *
                        *
                    */
                    if (board.Get(row + 1, col) == EMPTY && board.Get(row + 2, col) == piece && board.Get(row + 3, col) == piece) {
                        board.Set(row + 1, col, BLACK, true);
                        return true;
                    }
                }

                if (board.Get(row - 1, col + 1) == EMPTY && board.Get(row + 4, col - 4) == EMPTY ||
                    (board.Get(row - 1, col + 1) == piece || board.Get(row + 4, col - 4) == piece)
                    ) {
                    /*
                        *

                      *
                     *
                    */
                    if (board.Get(row + 1, col - 1) == EMPTY && board.Get(row + 2, col - 2) == piece && board.Get(row + 3, col - 3) == piece) {
                        board.Set(row + 1, col - 1, BLACK, true);
                        return true;
                    }

                    /*
                        *
                       *

                     *
                    */
                    if (board.Get(row + 1, col - 1) == piece && board.Get(row + 2, col - 2) == EMPTY && board.Get(row + 3, col - 3) == piece) {
                        board.Set(row + 2, col - 2, BLACK, true);
                        return true;
                    }
                }

                if (board.Get(row - 1, col - 1) == EMPTY && board.Get(row + 4, col + 4) == EMPTY ||
                    (board.Get(row - 1, col - 1) == piece || board.Get(row + 4, col + 4) == piece)
                    ) {
                    /*
                        *

                          *
                           *
                    */
                    if (board.Get(row + 1, col + 1) == EMPTY && board.Get(row + 2, col + 2) == piece && board.Get(row + 3, col + 3) == piece) {
                        board.Set(row + 1, col + 1, BLACK, true);
                        return true;
                    }

                    /*
                        *
                         *

                           *
                    */
                    if (board.Get(row + 1, col + 1) == piece && board.Get(row + 2, col + 2) == EMPTY && board.Get(row + 3, col + 3) == piece) {
                        board.Set(row + 2, col + 2, BLACK, true);
                        return true;
                    }
                }
            }
        }
    }

    return false;
}
