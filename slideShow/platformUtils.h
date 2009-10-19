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
 * file:         platformUtils.h
 *
 * function:
 *
 * description:  useful function and data declarations related to the windows
 *				 platform
 *
 * author:       Mohammed Safwat (MS)
 *
 * environment:  Microsoft Visual C++ 2008, Windows Mobile 6 Professional SDK,
 *				 windows xp profesional
 *
 * notes:        This is a private program.
 *
 ************************************************************/
#include <list>
#include <string>
#include <WinDef.h>
#ifdef _UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif
namespace Slideshow
{
    /**
    * @brief Path separator
    */
    extern const tstring pathSep;
    /**
    * @brief Returns the contents of the given directory with the specified
    * conditions
    *
    * @param[in] dirName	directory to return its contents
    * @param[in] pattern	pattern to filter contents
    * @param[in] attrFilter attributes to match with contents
    * return				contents of the given directory matching the
    *						specified conditions
    */
    const std::list< tstring > GetContents(const tstring& dirName,
        const tstring& pattern, const DWORD attrFilter) throw ();
}
