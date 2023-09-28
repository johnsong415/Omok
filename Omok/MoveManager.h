#pragma once

#include "framework.h"

#include <queue>
#include <vector>
#include <functional>



class MoveManager
{
public:
    MoveManager();
    ~MoveManager();

public:
    enum Direction
    {
        RIGHT = 0,
        DOWN,
        RIGHTDIAGONAL,
        LEFTDIAGONAL
    };

    struct Sequence
    {
        int priority;
        int row;
        int col;
        Piece piece;
        int stonesInSeries;
        int endsOfSequence;
        Direction direction;

        bool operator<(const Sequence& right) const
        {
            return priority < right.priority;
        }
    };

public:
    void AddSequence(int row, int col, Piece piece, int stonesInSeries, int index, int endOfSequence, Direction direction);
    void Clear();
    Sequence GetBestSequenceInfo();

private:
    std::priority_queue<Sequence> m_sequences;

};
