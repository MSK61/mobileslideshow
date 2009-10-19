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
 * file:         dirDlg.h
 *
 * function:
 *
 * description:  folder browse dialog box interface
 *
 * author:       Mohammed Safwat (MS)
 *
 * environment:  Microsoft Visual C++ 2008, Windows Mobile 6 Professional SDK,
 *				 windows xp profesional
 *
 * notes:        This is a private program.
 *
 ************************************************************/
#include "platformUtils.h"
namespace Slideshow
{
    /**
    * @brief Directory selected by the directory selection dialog box
    */
    extern tstring browseDirName;
    /**
    * @brief Processes messages directed to the director selection dialog
    *
    * @param[in] hwndDlg handle to the dialog box
    * @param[in] uMsg    message type identifier
    * @param[in] wParam  message-specific parameters
    * @param[in] lParam  message-specific parameters
    * @return            true if the message gets processed, otherwise false
    */
    INT_PTR CALLBACK DirDlgProc(
        HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
}
