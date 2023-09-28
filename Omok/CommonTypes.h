#pragma once



enum GameMode
{
    IDLE = 0,
    PVE,
    PVP
};

enum Turn
{
    NONE = 0,
    PLAYER1,
    PLAYER2,
    COMPUTER,
    HUMAN
};

enum Piece
{
    EMPTY,
    WHITE,
    BLACK
};

struct BoardCoordinates
{
    int x;
    int y;
};

struct Coordinates
{
    int x;
    int y;
};

struct Move
{
    Piece piece;
    BoardCoordinates coords;
};

struct Color
{
    float r;
    float g;
    float b;
};

const Color COLOR_DARK_RED = { 204, 0, 0 };
const Color COLOR_RED = { 255, 0, 0 };
const Color COLOR_GREEN = { 0, 255, 0 };
const Color COLOR_YELLOW = { 255, 255, 0 };
const Color COLOR_DARK_BLUE = { 0, 125, 0};
const Color COLOR_BLUE = { 0, 0, 255 };
const Color COLOR_PURPLE = { 168, 0, 168 };
const Color COLOR_BLACK = { 0, 0, 0 };
const Color COLOR_WHITE = { 255, 255, 255 };
const Color COLOR_OFF_YELLOW = { 187, 170, 64 };



#define SQUARE_LENGTH       30

#define BOARD_LENGTH        19
#define BOARD_HEIGHT        19

#define SCREEN_WIDTH        800
#define SCREEN_HEIGHT       800

#define SQUARE_SIDE_LENGTH  30
#define PIECE_RADIUS        20
