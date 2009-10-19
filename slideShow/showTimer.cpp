/************************************************************
 *
 * Copyright 2009 Mohammed El-Afifi
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
 * file:         showTimer.cpp
 *
 * function:	 ChangeImg
 *
 * description:  runtime logic of the display timer
 *
 * author:       Mohammed Safwat (MS)
 *
 * environment:  Microsoft Visual C++ 2008, Windows Mobile 6 Professional SDK,
 *				 windows xp profesional
 *
 * notes:        This is a private program.
 *
 ************************************************************/
#include "stdafx.h"
#include "showTimer.h"
namespace Slideshow
{
    using std::list;
    list< tstring >::const_iterator curBitmap;
    list< tstring >::const_iterator lastBitmap;
    HBITMAP curImgObj = NULL;
    HGDIOBJ initialDCObj = NULL;
    HDC inMemDC = NULL;
    void CALLBACK ChangeImg(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
    {
        RECT clientRect;
        HGDIOBJ oldImgObj;

        if (curBitmap == lastBitmap) DestroyWindow(hwnd);// end of image list
        else
        {

            /// Create a device context if no one already exists.
            if (inMemDC == NULL) inMemDC = CreateCompatibleDC(NULL);

            /// Load the current bitmap and associate it to the device context.
            curImgObj = SHLoadDIBitmap(curBitmap++ -> c_str());
            oldImgObj = SelectObject(inMemDC, curImgObj);

            if (inMemDC == NULL || curImgObj == NULL || oldImgObj == NULL)
                DestroyWindow(hwnd);/// Trap errors.

            // Maintain/clean up old data.
            if (initialDCObj == NULL) initialDCObj = oldImgObj;
            else DeleteObject(oldImgObj);

            /// Invalidate all the client area.
            GetClientRect(hwnd, &clientRect);
            InvalidateRect(hwnd, &clientRect, FALSE);

        }

    }
}
