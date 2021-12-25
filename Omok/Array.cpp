#include "Array.h"



Array::Array()
{
    m_default.row = 0;
    m_default.col = 0;
    m_default.piece = Square::EMPTY;
    m_default.stonesInSeries = 0;
    Clear();
}

Array::~Array()
{
}

Array::PieceInfo Array::FindLongestSeries()
{
    int largest = 0;
    PieceInfo result;

    for (int i = 0; i < NUMBEROFELEMENTS; ++i) {
        if (largest < m_arrayOfPieces[i].stonesInSeries) {
            result = m_arrayOfPieces[i];
            largest = m_arrayOfPieces[i].stonesInSeries;
        }
    }

    return result;
}

void Array::Clear()
{
    for (int i = 0; i < NUMBEROFELEMENTS; ++i) {
        m_arrayOfPieces[i] = m_default;
    }
}

void Array::InputInfo(int row, int col, Square::Piece piece, int stonesInSeries, int index, int endOfSequence, Direction direction)
{
    if (stonesInSeries < 2) { return; }
    if (stonesInSeries == 2 && piece == Square::BLACK) { return; }
    m_arrayOfPieces[index].row = row;
    m_arrayOfPieces[index].col = col;
    m_arrayOfPieces[index].piece = piece;
    m_arrayOfPieces[index].stonesInSeries = stonesInSeries;
    m_arrayOfPieces[index].endsOfSequence = endOfSequence;
    m_arrayOfPieces[index].direction = direction;
}

void Array::GetHighPriority(int* priorities)
{
    int index = 0;
    for (int i = 0; i < NUMBEROFELEMENTS; ++i) {
        if (m_arrayOfPieces[i].stonesInSeries == 0) { priorities[i] = -1; }
        if (m_arrayOfPieces[i].endsOfSequence == 0) {
            if (m_arrayOfPieces[i].stonesInSeries == 4) {
                priorities[i] = 5;
            }
            else if (m_arrayOfPieces[i].stonesInSeries == 3) {
                priorities[i] = 3;
            }
            else if (m_arrayOfPieces[i].stonesInSeries == 2) {
                priorities[i] = 1;
            }
        }
        else if (m_arrayOfPieces[i].endsOfSequence == 1) {
            if (m_arrayOfPieces[i].stonesInSeries == 4) {
                priorities[i] = 4;
            }
            else if (m_arrayOfPieces[i].stonesInSeries == 3) {
                priorities[i] = 0;
            }
            else if (m_arrayOfPieces[i].stonesInSeries == 2) {
                priorities[i] = 1;
            }
        }
        else if (m_arrayOfPieces[i].endsOfSequence == 2) {
            priorities[i] = -1;
        }
    }
}

Array::PieceInfo Array::Get(int index)
{
    return m_arrayOfPieces[index];
}

Array::PieceInfo Array::FindFive()
{
    for (int i = 0; i < NUMBEROFELEMENTS; ++i) {
        if (m_arrayOfPieces[i].stonesInSeries == 5) {
            return m_arrayOfPieces[i];
        }
    }
    
    return m_default;
}
