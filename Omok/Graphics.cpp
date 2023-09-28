#include "Graphics.h"


static Graphics g_graphics;


Graphics::Graphics()
{
    m_greenBrush = CreateSolidBrush(RGB(COLOR_GREEN.r, COLOR_GREEN.g, COLOR_GREEN.b));
    m_bgBrush = CreateSolidBrush(RGB(COLOR_OFF_YELLOW.r, COLOR_OFF_YELLOW.g, COLOR_OFF_YELLOW.b));
}

Graphics::~Graphics()
{
    DeleteObject(m_greenBrush);
    DeleteObject(m_bgBrush);

}

void Graphics::Initialize(HWND hWnd)
{
    g_graphics.m_hWnd = hWnd;
    g_graphics.m_hDC = GetDC(hWnd);
}

Graphics& Graphics::Get()
{
    return g_graphics;
}


void Graphics::Paint()
{
    Clear();
}

void Graphics::Clear()
{
    RECT CLIENT_AREA;
    CLIENT_AREA.left = 0;
    CLIENT_AREA.right = SCREEN_WIDTH;
    CLIENT_AREA.top = 0;
    CLIENT_AREA.bottom = SCREEN_HEIGHT;

    FillRect(m_hDC, &CLIENT_AREA, m_bgBrush);
}

void Graphics::DrawTextInRect(RECT* pRect, LPCWSTR string, int charCount)
{
    DrawText(m_hDC, string, charCount, pRect, DT_CENTER || DT_VCENTER);
}

void Graphics::DrawSquare(const Coordinates coordinates, Color color)
{
    if (coordinates.x < SQUARE_SIDE_LENGTH / 2 || coordinates.y < SQUARE_SIDE_LENGTH / 2 || coordinates.x > SCREEN_WIDTH - SQUARE_SIDE_LENGTH / 2 || coordinates.y > SCREEN_HEIGHT - SQUARE_SIDE_LENGTH / 2) return;
    SelectObject(m_hDC, GetStockObject(BLACK_PEN));
    SelectObject(m_hDC, GetStockObject(DC_BRUSH));

    SetDCBrushColor(m_hDC, RGB(color.r, color.g, color.b));

    Rectangle(
        m_hDC,
        static_cast<int>(coordinates.x) - SQUARE_SIDE_LENGTH / 2,
        static_cast<int>(coordinates.y) - SQUARE_SIDE_LENGTH / 2,
        static_cast<int>(coordinates.x) + SQUARE_SIDE_LENGTH / 2,
        static_cast<int>(coordinates.y) + SQUARE_SIDE_LENGTH / 2);
}

void Graphics::DrawCircle(int radius, const Coordinates coordinates, Color color)
{
    if (coordinates.x < radius / 2 || coordinates.y < radius / 2 || coordinates.x > SCREEN_WIDTH - radius / 2 || coordinates.y > SCREEN_HEIGHT - radius / 2) return;
    SelectObject(m_hDC, GetStockObject(BLACK_PEN));
    SelectObject(m_hDC, GetStockObject(DC_BRUSH));

    SetDCBrushColor(m_hDC, RGB(color.r, color.g, color.b));

    Ellipse(
        m_hDC,
        static_cast<int>(coordinates.x) - radius / 2,
        static_cast<int>(coordinates.y) - radius / 2,
        static_cast<int>(coordinates.x) + radius / 2,
        static_cast<int>(coordinates.y) + radius / 2);
}

void Graphics::TextWithColor(std::wstring string, Coordinates location, Color color)
{
    SetTextColor(m_hDC, RGB(color.r, color.b, color.g));
    TextOut(m_hDC, location.x, location.y, string.c_str(), string.size());
}

void Graphics::LineFromTo(const Coordinates from, const Coordinates to)
{
    MoveToEx(m_hDC, from.x, from.y, nullptr);
    LineTo(m_hDC, to.x, to.y);
}

void Graphics::Message(std::wstring message, std::wstring title)
{
    MessageBox(m_hWnd, message.c_str(), title.c_str(), MB_OK);
}
