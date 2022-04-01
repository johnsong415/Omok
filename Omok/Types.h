#pragma once

enum GameMode
{
    IDLE = 0,
    PVE,
    PVP
};

enum Player
{
    SERVER = 0,
    CLIENT
};

struct Move
{
    int x;
    int y;
};
