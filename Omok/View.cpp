#include "View.h"

#include "Graphics.h"


View::View()
{
}

View::~View()
{}

void View::Paint(const Board& board, GameMode gameMode, Turn turn)
{
    // clear
    Graphics::Get().Clear();
    // grid lines
    for (int i = 1; i < 20; ++i) {
        Graphics::Get().LineFromTo({ SQUARE_SIDE_LENGTH, SQUARE_SIDE_LENGTH * i }, { SQUARE_SIDE_LENGTH * BOARD_LENGTH, SQUARE_SIDE_LENGTH * i });
        Graphics::Get().LineFromTo({ SQUARE_SIDE_LENGTH * i, SQUARE_SIDE_LENGTH }, { SQUARE_SIDE_LENGTH * i, SQUARE_SIDE_LENGTH * BOARD_HEIGHT });
    }

    board.IterateOverBoard(
        [](int row, int col, Piece piece) {
            if (piece == EMPTY) return;
            Color color;
            if (piece == WHITE) color = COLOR_WHITE;
            else if (piece == BLACK) color = COLOR_BLACK;
            Graphics::Get().DrawCircle(PIECE_RADIUS, { SQUARE_SIDE_LENGTH * (col + 1), SQUARE_SIDE_LENGTH * (row + 1) }, color);
        });

    // indicate whether game should be started
    if (gameMode == IDLE) {
        Graphics::Get().TextWithColor(L"Choose a game mode", { 0, 0 }, COLOR_DARK_RED);
    }
    else {
        if (turn == PLAYER1) Graphics::Get().TextWithColor(L"Player 1's turn", { 0, 0 }, COLOR_DARK_BLUE);
        else if (turn == PLAYER2) Graphics::Get().TextWithColor(L"Player 2's turn", { 0, 0 }, COLOR_DARK_RED);
        else if (turn == HUMAN) Graphics::Get().TextWithColor(L"Your turn", { 0, 0 }, COLOR_DARK_BLUE);
    }
}

bool View::TranslatePoint(const POINT& coordinates, BoardCoordinates& point)
{
    int xIndex = (int)(round(((double)coordinates.x) / SQUARE_LENGTH));
    int yIndex = (int)(round(((double)coordinates.y) / SQUARE_LENGTH));
    if (xIndex > 20 || yIndex > 20 || xIndex < 1 || yIndex < 1) return false;

    point = { yIndex - 1, xIndex - 1 };
    return true;
}
