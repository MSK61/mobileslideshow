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
 * file:         platformUtils.cpp
 *
 * function:     GetContents
 *
 * description:  useful function and data definitions related to the windows
 *               platform
 *
 * author:       Mohammed Safwat (MS)
 *
 * environment:  Microsoft Visual C++ 2008, Windows Mobile 6 Professional SDK,
 *               windows xp profesional
 *
 * notes:        This is a private program.
 *
 ************************************************************/
#include "stdafx.h"
#include "PlatformUtils.h"
namespace Slideshow
{
    using std::list;
    const tstring pathSep = _T("\\");
    const list< tstring > GetContents(const tstring& dirName,
        const tstring& pattern, const DWORD attrFilter) throw ()
    {
        WIN32_FIND_DATA itemInfo;
        const HANDLE itemIter =
            FindFirstFile((dirName + pathSep + pattern).c_str(), &itemInfo);
        list< tstring > contents;

        if (itemIter != INVALID_HANDLE_VALUE)
        {

            // Add contents matching the provided filter only.
            do if ((itemInfo.dwFileAttributes & attrFilter) == attrFilter)
                contents.push_back(itemInfo.cFileName);
            while (FindNextFile(itemIter, &itemInfo));

            FindClose(itemIter);

        }

        return contents;

    }
}
