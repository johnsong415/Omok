#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Initialize(HWND hWnd, HDC hDC)
{
    m_board.Initialize(hWnd, hDC, SQUARELENGTH);
    m_computer.Initialize(&m_board);
    Update();
    m_computer.MakeMove();
}

void Game::Update()
{
    m_board.Paint();
}

void Game::TranslateClick(POINTS point)
{
    if (m_gameOver) { return; }
    int yIndex = RoundFloatToInt(((double) point.x) / SQUARELENGTH);
    int xIndex = RoundFloatToInt(((double) point.y) / SQUARELENGTH);
    if (xIndex > 19 || yIndex > 19) { return; }
    bool ret = m_board.UpdateSquare(xIndex - 1, yIndex - 1, Square::WHITE);
    if (!ret) {
        return;
    }
    ret = CheckGameOver();
    if (ret) {
        m_gameOver = true;
        return;
    }
    Update();
    m_computer.MakeMove();
    Update();
    ret = CheckGameOver();
    if (ret) {
        m_gameOver = true;
        return;
    }
}

int Game::RoundFloatToInt(double val)
{
    int intVal = 0;
    while (val > 1) {
        --val;
        ++intVal;
    }
    if (val > 0.4) { ++intVal; }
    return intVal;
}

bool Game::CheckGameOver()
{
    Square::Piece winner = m_computer.Winner();

    if (winner != Square::EMPTY) {
        m_board.WinMessage(winner);
        return true;
    }
    return false;
}

void Game::Undo()
{
    bool ret = m_board.Undo();
    if (ret) {
        m_computer.MakeMove();
    }
}

void Game::Restart()
{
    m_board.ResetBoard();
    m_gameOver = false;
    m_computer.MakeMove();
}
