#pragma once

#include "framework.h"
#include "Square.h"


// list that contains previous moves
class MoveList
{
public:
    MoveList();
    ~MoveList();

public:
    struct Move
    {
        int row;
        int col;
        Square::Piece color;
    };

    struct Node
    {
        Move move;
        Node* nextNode;
    };

public:
    void Add(int row, int col, Square::Piece color);
    Move Delete();
    Move Retrieve();

private:
    Node* m_head;
};
