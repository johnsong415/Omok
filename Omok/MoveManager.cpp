#include "MoveManager.h"



MoveManager::MoveManager()
{
}

MoveManager::~MoveManager()
{
}

void MoveManager::Clear()
{
    m_sequences = std::priority_queue<Sequence>();
}

void MoveManager::AddSequence(int row, int col, Piece piece, int stonesInSeries, int index, int endOfSequence, Direction direction)
{
    if (stonesInSeries < 2) { return; }
    if (stonesInSeries == 2 && piece == BLACK) { return; }

    int priority = 0;

    if (stonesInSeries == 5) {
        priority = 6;
    }

    if (stonesInSeries == 0) priority = -1;
    if (endOfSequence == 0) {
        if (stonesInSeries == 4) {
            priority = 5;
        }
        else if (stonesInSeries == 3) {
            priority = 3;
        }
        else if (stonesInSeries == 2) {
            priority = 1;
        }
    }
    else if (endOfSequence == 1) {
        if (stonesInSeries == 4) {
            priority = 4;
        }
        else if (stonesInSeries == 3) {
            priority = 0;
        }
        else if (stonesInSeries == 2) {
            priority = 1;
        }
    }
    else if (endOfSequence == 2) {
        priority = -1;
    }
    Sequence newMove = {priority, row, col, piece, stonesInSeries, endOfSequence, direction};

    m_sequences.emplace(newMove);
}

MoveManager::Sequence MoveManager::GetBestSequenceInfo()
{
    if (m_sequences.empty()) return { -1, -1, -1, EMPTY, -1, -1, DOWN };
    Sequence highestPriority = m_sequences.top();
    m_sequences.pop();
    return highestPriority;
}
