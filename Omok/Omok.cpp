// Omok.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Omok.h"
#include "Game.h"
#include "Messaging.h"
#include "Network.h"

#include <Commctrl.h>


#define MAX_LOADSTRING 100


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND hWnd;                                      // Handle to window
Game game;                                      // Game class


void OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
void OnKeyDown(WPARAM wParam, LPARAM lParam);
void OpenServerAddressDialogBox(HWND hOwnerWindow);

void OnStartServer();
void OnConnectToServer(DWORD ipAddress);




// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_OMOK, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OMOK));

    Messaging::Initialize();

    game.Initialize(hWnd, GetDC(hWnd));

    MSG msg;
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_DESTROY || msg.message == WM_QUIT) {
                break;
            }

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        Network::NetworkUpdate();
    }

    return 0;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OMOK));
    wcex.hCursor        = LoadCursorFromFile(L"arrow.cur");
    wcex.hbrBackground  = (CreateSolidBrush(RGB(187, 170, 64)));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_OMOK);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      0, 0, 1100, 1100, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_LBUTTONDOWN:
        POINTS point = MAKEPOINTS(lParam);
        game.TranslateClick(point);
        break;

    case WM_KEYDOWN:
        OnKeyDown(wParam, lParam);
        break;

    case WM_COMMAND:
        OnCommand(hWnd, wParam, lParam);
        return DefWindowProc(hWnd, message, wParam, lParam);

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    int wmId = LOWORD(wParam);

    // Parse the menu selections:
    switch (wmId)
    {
    case IDM_ABOUT:
        DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
        break;

    case IDM_PVE_TRUE:
        game.InitPVE();
        break;

    case IDM_EXIT:
        DestroyWindow(hWnd);
        break;

    case IDM_FILE_STARTSERVER:
        OnStartServer();
        break;

    case IDM_FILE_CONNECTTOSERVER:
        OpenServerAddressDialogBox(hWnd);
        break;
    }
}

void OnKeyDown(WPARAM wParam, LPARAM lParam)
{
    switch (wParam)
    {
    case 'B':
    case 'b':
        game.Undo();
        break;
    case 'R':
    case 'r':
        game.Restart();
        break;
    }
}

void OpenServerAddressDialogBox(HWND hOwnerWindow)
{
    DialogBox(
        hInst,
        MAKEINTRESOURCE(IDD_SERVER_ADDRESS),
        hOwnerWindow,
        [](HWND hDialog, UINT message, WPARAM wParam, LPARAM lParam) -> INT_PTR {
            switch (message) {
            case WM_INITDIALOG:
                return (INT_PTR) TRUE;

            case WM_COMMAND:
                if (LOWORD(wParam) == IDCANCEL) {
                    EndDialog(hDialog, LOWORD(wParam));
                    return (INT_PTR) TRUE;
                }

                if (LOWORD(wParam) == IDOK) {
                    DWORD ipAddress = 0;
                    SendDlgItemMessage(hDialog, IDC_SERVER_ADDRESS, IPM_GETADDRESS, 0, (LPARAM) &ipAddress);
                    EndDialog(hDialog, LOWORD(wParam));
                    OnConnectToServer(ipAddress);
                    return (INT_PTR) TRUE;
                }
                break;
            }

            return (INT_PTR) FALSE;
        });
}

void OnStartServer()
{
    bool started = Network::StartServer();
    if (!started) {
        MessageBox(hWnd, L"Failed to start server!", L"Error", MB_ICONEXCLAMATION | MB_OK);
        return;
    }

    game.InitServer();
}

void OnConnectToServer(DWORD ipAddress)
{
    bool connected = Network::ConnectToServer(ipAddress);
    if (!connected) {
        MessageBox(hWnd, L"Failed to connect to server!", L"Error", MB_ICONEXCLAMATION | MB_OK);
        return;
    }

    game.InitClient();
}
