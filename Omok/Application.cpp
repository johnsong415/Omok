#include "Application.h"
#include "Graphics.h"


Application g_application;

Application::Application()
{}

Application::~Application()
{}

Application& Application::Get()
{
    return g_application;
}

void Application::Initialize(HWND hWnd)
{
    Graphics::Get().Initialize(hWnd);

    PaintView();
}

void Application::OnLButtonDown(POINT point)
{
    BoardCoordinates boardCoord;
    bool validPoint = m_view.TranslatePoint(point, boardCoord);

    if (!validPoint) return;

    m_game.MakeMove(boardCoord);
    PaintView();
}

void Application::OnKeyDown(unsigned char virtualKey)
{
    switch (virtualKey) {
    case 'U':
        m_game.Undo();
        PaintView();
        break;
    case 'R':
        m_game.Reset();
        PaintView();
        break;
    }
}

void Application::OnPaint()
{
    PaintView();
}

void Application::StartPVE()
{
    m_game.SetGameMode(PVE);
    m_game.MakeAIMove();
    PaintView();
}

void Application::StartPVP()
{
    m_game.SetGameMode(PVP);
    PaintView();
}

void Application::PaintView()
{
    m_view.Paint(m_game.GetBoard(), m_game.GetGameMode(), m_game.GetTurn());
}
