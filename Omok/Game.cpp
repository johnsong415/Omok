#include "Game.h"
#include "Graphics.h"


Game::Game()
{
}

Game::~Game()
{}

void Game::MakeMove(BoardCoordinates coords)
{
    if (m_gameMode == IDLE) return;

    Piece piece = EMPTY;
    // PVE
    if (m_currentTurn == HUMAN) piece = WHITE;
    // PVP
    else if (m_currentTurn == PLAYER1) piece = BLACK;
    else if (m_currentTurn == PLAYER2) piece = WHITE;

    bool success = m_board.Set(coords.x, coords.y, piece, false);
    if (!success) return;

    

    bool gameOver = CheckGameOver();
    if (gameOver) {
        SetGameMode(IDLE);
    }
    // PVE
    if (m_currentTurn == HUMAN) MakeAIMove();
    // PVP
    else if (m_currentTurn == PLAYER1) m_currentTurn = PLAYER2;
    else if (m_currentTurn == PLAYER2) m_currentTurn = PLAYER1;
}

void Game::MakeAIMove()
{
    m_computer.MakeMove(m_board);
    m_currentTurn = HUMAN;
    bool gameOver = CheckGameOver();
    if (gameOver) {
        SetGameMode(IDLE);
    }
}

bool Game::CheckGameOver()
{
    Piece winner = m_computer.Winner(m_board);

    if (winner != EMPTY) {
        if (winner == WHITE) Graphics::Get().Message(L"White won", L"White won");
        else if (winner == BLACK) Graphics::Get().Message(L"Black won", L"Black won");
        return true;
    }
    return false;
}


void Game::SetGameMode(GameMode newGameMode)
{
    if (m_gameMode != IDLE && newGameMode != IDLE) return;
    m_board.ResetBoard();
    m_gameMode = newGameMode;

    if (m_gameMode == PVE) m_currentTurn = COMPUTER;
    else if (m_gameMode == PVP) m_currentTurn = PLAYER1;
    else if (m_gameMode == IDLE) m_currentTurn = NONE;
}

const Board& Game::GetBoard()
{
    return m_board;
}

GameMode Game::GetGameMode()
{
    return m_gameMode;
}

Turn Game::GetTurn()
{
    return m_currentTurn;
}

void Game::Undo()
{
    if (m_gameMode == PVE) {
        // AI is always black, player is always white
        // TODO: this does not erase twice!
        MoveStack::Move lastMove = m_board.MoveListPop();
        m_board.Set(lastMove.row, lastMove.col, EMPTY, false);
        if (lastMove.color == BLACK) {
            Undo();
        }
    }
    else if (m_gameMode == PVP) {
        MoveStack::Move lastMove = m_board.MoveListPop();
        m_board.Set(lastMove.row, lastMove.col, EMPTY, false);
        m_currentTurn = (m_currentTurn == PLAYER1) ? PLAYER2 : PLAYER1;
    }
}

void Game::Reset()
{
    if (m_gameMode == IDLE) return;
    m_board.ResetBoard();

    if (m_gameMode == PVE) {
        MakeAIMove();
    }
    else if (m_gameMode == PVP) {
        m_currentTurn = PLAYER1;
    }
}

