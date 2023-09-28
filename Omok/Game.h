#pragma once

#include "Board.h"
#include "Computer.h"

#include "MoveList.h"

class Game
{
public:
    Game();
    ~Game();

public:
    void MakeMove(BoardCoordinates coords);
    void MakeAIMove();

    void SetGameMode(GameMode newGameMode);

    bool CheckGameOver();

    const Board& GetBoard();
    GameMode GetGameMode();
    Turn GetTurn();

    void Undo();
    void Reset();

private:
    Board m_board;
    Computer m_computer;
    MoveStack m_moveList;

    Turn m_currentTurn = NONE;
    GameMode m_gameMode = IDLE;

};

