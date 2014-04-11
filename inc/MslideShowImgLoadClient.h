/*
 ========================================================================
 Name        : MslideShowImgLoadClient.h
 Author      : Mohammed Safwat
 Copyright   : 2009, 2010, 2014 Mohammed El-Afifi
 This file is part of slideShow.

 slideShow is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 slideShow is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with slideShow.  If not, see <http://www.gnu.org/licenses/>.

 Description : represents the interface MslideShowImgLoadClient
 ========================================================================
 */

#ifndef MSLIDESHOWIMGLOADCLIENT_H_
#define MSLIDESHOWIMGLOADCLIENT_H_
#include "e32def.h"

class CFbsBitmap;
namespace Slideshow
    {

    /**
     * @brief Image loading observer
     */
    class MslideShowImgLoadClient
        {
    public:
        virtual ~MslideShowImgLoadClient();
        /**
         * @brief Callback to notify this observer of image loading completion
         *
         * @param[in] aLoadRes result of the image loading
         * @param[in] aImgObj  image object containing the loaded image
         */
        virtual void HandleImg(TInt aLoadRes, const CFbsBitmap& aImgObj) = 0;
        };

    }

#endif /* MSLIDESHOWIMGLOADCLIENT_H_ */
