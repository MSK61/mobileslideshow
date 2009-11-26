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
 * file:         showTimer.h
 *
 * function:
 *
 * description:  image display timer interface
 *
 * author:       Mohammed Safwat (MS)
 *
 * environment:  Microsoft Visual C++ 2008, Windows Mobile 6 Professional SDK,
 *               windows xp profesional
 *
 * notes:        This is a private program.
 *
 ************************************************************/
#include "platformUtils.h"
namespace Slideshow
{
    /**
    * @brief Current bitmap to be displayed
    */
    extern std::list< tstring >::const_iterator curBitmap;
    /**
    * @brief Last bitmap to be displayed(one past the end)
    */
    extern std::list< tstring >::const_iterator lastBitmap;
    /**
    * @brief Current image object handle
    *
    * The image object should be reclaimed by the user code.
    */
    extern HBITMAP curImgObj;
    /**
    * @brief Handle of the original object of the in-memory device context
    *
    * The initial object should be restored by the user code.
    */
    extern HGDIOBJ initialDCObj;
    /**
    * @brief In-memory device context storing the bitmap
    *
    * The device context should be reclaimed by the user code.
    */
    extern HDC inMemDC;
    /**
    * @brief Image displaying timer callback
    *
    * @param[in] hwnd    handle to the window associated with the timer
    * @param[in] uMsg    message type identifier
    * @param[in] idEvent timer identifier
    * @param[in] dwTime  number of milliseconds that have elapsed since the
    *                    system was started
    */
    void CALLBACK ChangeImg(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);
}
