#pragma once

#include "framework.h"
#include "Square.h"


#define NUMBEROFELEMENTS            200

// array that contains all useful pieces
class Array
{
public:
    Array();
    ~Array();

public:
    enum Direction
    {
        RIGHT = 0,
        DOWN,
        RIGHTDIAGONAL,
        LEFTDIAGONAL
    };

    struct PieceInfo
    {
        int row;
        int col;
        Square::Piece piece;
        int stonesInSeries;
        int endsOfSequence;
        Direction direction;
    };

public:
    PieceInfo FindLongestSeries();
    void InputInfo(int row, int col, Square::Piece piece, int stonesInSeries, int index, int endOfSequence, Direction direction);
    void Clear();
    void GetHighPriority(int* priorities);
    PieceInfo Get(int index);
    PieceInfo FindFive();

private:
    PieceInfo m_default;
    PieceInfo m_arrayOfPieces[NUMBEROFELEMENTS];
    
};
