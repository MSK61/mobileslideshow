/*
========================================================================
 Name        : CImgLoader.h
 Author      : Mohammed Safwat
 Copyright   : 2009 Mohammed El-Afifi
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

 Description : represents the interface of the class CImgLoader
========================================================================
*/

#ifndef CIMGLOADER_H_
#define CIMGLOADER_H_

#include <e32base.h>
#include <f32file.h>

class CFbsBitmap;
class CImageDecoder;
namespace Slideshow
    {

    class MImgLoadClient;
    /**
     * @brief Asynchronous image loader
     */
    class CImgLoader : public CActive
        {
    public:
        /**
         * Initializes the path upon which the loader will work
         *
         * @param     aObserver object to receive image loading completion
         *                      notifications
         */
        CImgLoader(MImgLoadClient& aObserver);
        /**
         * @brief Starts loading an image asynchronously
         *
         * The registered observer with this image loader is notified upon
         * completion(or otherwise failures).
         *
         * @param[in] aFilePath image file name
         */
        void LoadImgL(const TFileName& aFileName);
    protected:
        void DoCancel(void);
        /**
         * @brief Notifies the observer about the image loading status
         *
         * The observer should copy any needed information from the passed image
         * object token as it'll be destroyed directly after the notification.
         */
        void RunL(void);
    private:
        /**
         * @brief Cleans up a single image loading request
         */
        void EndLoad(void);
        /**
        * @brief Image object to store the loaded image in
        */
        CFbsBitmap* iImgObj;
        /**
         * @brief Filesystem session
         */
        RFs iFilesys;
        /**
         * @brief Image loading and decoding facility
         */
        CImageDecoder* iImgLoader;
        /**
         * @brief object to receive image loading completion notifications
         */
        MImgLoadClient& iObserver;
        };

    }

#endif /* CIMGLOADER_H_ */
