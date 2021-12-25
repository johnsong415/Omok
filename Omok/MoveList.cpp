#include "MoveList.h"


MoveList::MoveList()
{
    m_head = nullptr;
}

MoveList::~MoveList()
{
    Node* current = m_head;
    Node* next = m_head->nextNode;
    while (current != nullptr) {
        delete current;
        current = next;
        if (next != nullptr) {
            next = next->nextNode;
        }
    }
}

void MoveList::Add(int row, int col, Square::Piece color)
{
    Node* newNode = new Node;
    Move move;
    move.row = row;
    move.col = col;
    move.color = color;
    newNode->move = move;
    newNode->nextNode = m_head;
    m_head = newNode;
}

MoveList::Move MoveList::Delete()
{
    if (m_head == nullptr) {
        Move ret;
        ret.col = 0;
        ret.row = 0;
        ret.color = Square::EMPTY;
        return ret;
    }
    Node* newHead = m_head->nextNode;
    Move ret = m_head->move;
    delete m_head;
    m_head = newHead;
    return ret;
}

MoveList::Move MoveList::Retrieve()
{
    if (m_head == nullptr) {
        Move ret;
        ret.col = 0;
        ret.row = 0;
        ret.color = Square::EMPTY;
        return ret;
    }
    return m_head->move;
}
