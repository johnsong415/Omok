#pragma once

#include "framework.h"

#include "CommonTypes.h"
#include "Board.h"



class View
{
public:
    View();
    ~View();

public:
    void Paint(const Board& board, GameMode gameMode, Turn turn);

    bool TranslatePoint(const POINT& coordinates, BoardCoordinates& point);
};
