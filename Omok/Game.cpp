#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Initialize(HWND hWnd, HDC hDC)
{
    m_board.Initialize(hWnd, hDC, SQUARELENGTH, &m_myTurn, &m_gameMode, &m_wins, &m_losses);
    m_computer.Initialize(&m_board);
    Update();
}

void Game::InitServer()
{
    m_gameMode = PVP;
    m_player = SERVER;
    m_myTurn = false;
    m_color = Square::WHITE;

    RegisterHandlers();
}

void Game::InitClient()
{
    m_gameMode = PVP;
    m_player = CLIENT;
    m_myTurn = true;
    m_color = Square::BLACK;

    RegisterHandlers();
}

void Game::RegisterHandlers()
{
    Messaging::RegisterMovePacketHandler([this](int x, int y) { OnMoveReceived(x, y); });
}

void Game::InitPVE()
{
    m_gameMode = PVE;
    m_myTurn = true;
    Restart();
    m_color = Square::WHITE;
}

void Game::Update()
{
    m_board.Paint();
}

void Game::TranslateClick(POINTS point)
{
    if (m_gameOver || !m_myTurn) { return; }
    int yIndex = RoundFloatToInt(((double) point.x) / SQUARELENGTH);
    int xIndex = RoundFloatToInt(((double) point.y) / SQUARELENGTH);
    if (xIndex > 19 || yIndex > 19) { return; }
    if (!m_board.UpdateSquare(xIndex - 1, yIndex - 1, m_color)) {
        return;
    }
    
    Update();
    
    if (m_gameMode == PVE) {
        if (CheckGameOver()) {
            return;
        }
        m_computer.MakeMove();
        Update();
    }
    else if (m_gameMode == PVP) {
        Messaging::SendMove(xIndex - 1, yIndex - 1);
        CheckGameOver();
        m_myTurn = false;
        Update();
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
        m_gameOver = true;
        if (winner == m_color) { ++m_wins; }
        if (winner != m_color) { ++m_losses; }
        if (m_gameMode == PVP && m_player == CLIENT) {
            Messaging::CloseClientSocket();
        }
        return true;
    }
    return false;
}

void Game::Undo()
{
    if (m_gameMode != PVE) { return; }
    
    bool ret = m_board.Undo();
    if (ret) {
        m_computer.MakeMove();
    }
}

void Game::Restart()
{
    if (m_gameMode != PVE) { return; }

    m_board.ResetBoard();
    m_gameOver = false;
    m_computer.MakeMove();
}

void Game::OnMoveReceived(int x, int y)
{
    if (x < 0 || y < 0 || x > 19 || y > 19 || m_myTurn) {
        return; // bad request
    }

    if (m_player == SERVER) {
        m_board.UpdateSquare(x, y, Square::BLACK);
    }
    else if (m_player == CLIENT) {
        m_board.UpdateSquare(x, y, Square::WHITE);
    }
    CheckGameOver();
    m_myTurn = true;
    Update();
}
