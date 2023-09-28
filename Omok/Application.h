#pragma once

#include "View.h"
#include "Board.h"
#include "Game.h"




class Application
{
public:
    Application();
    ~Application();

public:
    static Application& Get();

public:
    void Initialize(HWND hWnd);

    void OnLButtonDown(POINT point);
    void OnKeyDown(unsigned char virtualKey);
    void OnPaint();

    void StartPVE();
    void StartPVP();

private:
    void PaintView();

private:
    View m_view;
    Game m_game;
};
