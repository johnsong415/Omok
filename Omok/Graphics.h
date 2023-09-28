#pragma once

#include "framework.h"

#include <string>

class Graphics
{
public:
    Graphics();
    ~Graphics();

public:
    static void Initialize(HWND hWnd);
    static Graphics& Get();

public:
    void Paint();

    void Clear();
    void DrawSquare(const Coordinates coordinates, Color color);
    void DrawCircle(int radius, const Coordinates coordinates, Color color);

    void DrawTextInRect(RECT* pRect, LPCWSTR string, int charCount);

    void TextWithColor(std::wstring string, Coordinates location, Color color);

    void LineFromTo(const Coordinates from, const Coordinates to);

    void Message(std::wstring message, std::wstring title);

private:
    HWND m_hWnd = NULL;
    HDC m_hDC = NULL;

private:
    HBRUSH m_greenBrush = NULL;
    HBRUSH m_bgBrush = NULL;
};
