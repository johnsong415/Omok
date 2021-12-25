#include "Square.h"


Square::Square()
{
    m_piece = EMPTY;
}

Square::~Square()
{
}

Square::Piece Square::GetPiece()
{
    return m_piece;
}

void Square::NewPiece(Square::Piece piece)
{
    m_piece = piece;
}

void Square::Paint(HDC hDC, int x, int y, int pieceRadius, bool last)
{
    if (m_piece == EMPTY) { return; }
    SelectObject(hDC, GetStockObject(DC_BRUSH));
    if (m_piece == WHITE) {
        SetDCBrushColor(hDC, RGB(255, 255, 255));
        SetBkColor(hDC, RGB(255, 255, 255));
    }
    else if (m_piece == BLACK) {
        SetDCBrushColor(hDC, RGB(0, 0, 0));
        SetBkColor(hDC, RGB(0, 0, 0));
    }
    

    Ellipse(hDC, x - pieceRadius, y - pieceRadius, x + pieceRadius, y + pieceRadius);
    
    if (last) {
        SetTextColor(hDC, RGB(225, 0, 0));
        ExtTextOut(hDC, x - pieceRadius / 4, y - pieceRadius / 4, ETO_CLIPPED, nullptr, L"P", 1, nullptr);
    }
}
