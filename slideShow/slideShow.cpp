/************************************************************
 *
 * Copyright 2009, 2014 Mohammed El-Afifi
 * This file is part of slideShow.
 *
 * slideShow is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * slideShow is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with slideShow.  If not, see <http://www.gnu.org/licenses/>.
 *
 * file:         slideShow.cpp
 *
 * function:     GetBmpFiles, InitInstance, MyRegisterClass, WinMain, and
 *               WndProc
 *
 * description:  runtime logic of the application window
 *
 * author:       Mohammed Safwat (MS)
 *
 * environment:  Microsoft Visual C++ 2008, Windows Mobile 6 Professional SDK,
 *               windows xp profesional
 *
 * notes:        This is a private program.
 *
 ************************************************************/
// slideShow.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "dirDlg.h"
#include "showTimer.h"
#include "slideShow.h"
#include <windows.h>
#include <commctrl.h>

#define MAX_LOADSTRING 100

using namespace Slideshow;
using std::list;

// Global Variables:
HINSTANCE			g_hInst;			// current instance
HWND				g_hWndMenuBar;		// menu bar handle

// Forward declarations of functions included in this code module:
ATOM			MyRegisterClass(HINSTANCE, LPTSTR);
BOOL			InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

namespace
{
    /**
    * @brief Returns the bitmap files inside the given directory
    *
    * @param[in] dirName directory to return bitmap files inside
    * return             bitmap files inside the given directory, with their
    *                    full path
    */
    const list< tstring > GetBmpFiles(const tstring& dirName) throw ()
    {
        static const TCHAR bmpPattern[] = _T("*.bmp");// bitmap file conditions
        list< tstring > bmpFiles = GetContents(dirName, bmpPattern, 0);
        list< tstring >::iterator curFile = bmpFiles.begin();
        const list< tstring >::iterator lastFile = bmpFiles.end();

        for (; curFile != lastFile; curFile++)
            *curFile = dirName + pathSep + *curFile;

        return bmpFiles;

    }
}

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPTSTR    lpCmdLine,
                   int       nCmdShow)
{
    MSG msg;

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }


    // Main message loop:
    while (GetMessage(&msg, NULL, 0, 0))
    {
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
ATOM MyRegisterClass(HINSTANCE hInstance, LPTSTR szWindowClass)
{
    WNDCLASS wc;

    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SLIDESHOW));
    wc.hCursor       = 0;
    wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName  = 0;
    wc.lpszClassName = szWindowClass;

    return RegisterClass(&wc);
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
    HWND hWnd;
    TCHAR szTitle[MAX_LOADSTRING];		// title bar text
    TCHAR szWindowClass[MAX_LOADSTRING];	// main window class name

    g_hInst = hInstance; // Store instance handle in our global variable

    // SHInitExtraControls should be called once during your application's initialization to initialize any
    // of the device specific controls such as CAPEDIT and SIPPREF.
    SHInitExtraControls();

    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_SLIDESHOW, szWindowClass, MAX_LOADSTRING);

    //If it is already running, then focus on the window, and exit
    hWnd = FindWindow(szWindowClass, szTitle);
    if (hWnd)
    {
        // set focus to foremost child window
        // The "| 0x00000001" is used to bring any owned windows to the foreground and
        // activate them.
        SetForegroundWindow((HWND)((ULONG) hWnd | 0x00000001));
        return 0;
    }

    if (!MyRegisterClass(hInstance, szWindowClass))
    {
        return FALSE;
    }

    hWnd = CreateWindow(szWindowClass, szTitle, WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

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
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static list< tstring > bmpFiles;
    BITMAP bmpImg;
    RECT clientRect;
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;
    static const UINT timerID = 1;
    // time period every which a new image should be displayed
    static const UINT turnOverPeriod = 2000;


    switch (message)
    {
    case WM_COMMAND:
        wmId    = LOWORD(wParam);
        wmEvent = HIWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_OK:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;
    case WM_CREATE:
        SHMENUBARINFO mbi;

        memset(&mbi, 0, sizeof(SHMENUBARINFO));
        mbi.cbSize     = sizeof(SHMENUBARINFO);
        mbi.hwndParent = hWnd;
        mbi.nToolBarId = IDR_MENU;
        mbi.hInstRes   = g_hInst;

        if (!SHCreateMenuBar(&mbi))
        {
            g_hWndMenuBar = NULL;
        }
        else
        {
            g_hWndMenuBar = mbi.hwndMB;
        }

        /// Prompt the user for a folder.
        DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIR_DLG), hWnd, DirDlgProc);
        /// Get the bitmap images to be displayed.
        bmpFiles = GetBmpFiles(browseDirName);
        /// Initialize the image display sequence.
        curBitmap = bmpFiles.begin();
        lastBitmap = bmpFiles.end();
        /// Simulate an initial timer tick to display the first image.
        ChangeImg(hWnd, WM_TIMER, timerID, GetTickCount());
        /// Start the timer.
        SetTimer(hWnd, timerID, turnOverPeriod, ChangeImg);
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        // TODO: Add any drawing code here...
        /// Draw the bitmap.
        if (inMemDC != NULL)
        {

            GetObject(curImgObj, sizeof(bmpImg), &bmpImg);
            GetClientRect(hWnd, &clientRect);
            StretchBlt(hdc, 0, 0, clientRect.right, clientRect.bottom, inMemDC,
                0, 0, bmpImg.bmWidth, bmpImg.bmHeight, SRCCOPY);

        }

        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:

        KillTimer(hWnd, timerID);/// Stop the timer.

        // GDI clean-up
        if (inMemDC != NULL)
        {

            SelectObject(inMemDC, initialDCObj);
            DeleteObject(curImgObj);
            DeleteDC(inMemDC);

        }

        CommandBar_Destroy(g_hWndMenuBar);
        PostQuitMessage(0);
        break;


    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

