/*
========================================================================
 Name        : CslideShowImgLoader.h
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

 Description : represents the interface of the class CslideShowImgLoader
========================================================================
*/

#ifndef CSLIDESHOWIMGLOADER_H_
#define CSLIDESHOWIMGLOADER_H_

#include <e32base.h>
#include <f32file.h>

class CFbsBitmap;
class CImageDecoder;
namespace Slideshow
    {

    class MslideShowImgLoadClient;
    /**
     * @brief Asynchronous image loader
     */
    class CslideShowImgLoader : public CActive
        {
    public:
        ~CslideShowImgLoader();
        /**
         * @brief Starts loading an image asynchronously
         *
         * The registered observer with this image loader is notified upon
         * completion(or otherwise failures).
         *
         * @param[in] aFilePath image file name
         */
        void LoadImgL(const TFileName& aFileName);
        /**
         * @brief Two-phase constructor
         *
         * @param[in] aImgTwipSize desired image size in twips
         * @param     aObserver    object to receive image loading completion
         *                         notifications
         */
        static CslideShowImgLoader* const NewL(const TSize& aImgTwipSize,
            MslideShowImgLoadClient& aObserver);
    protected:
        void DoCancel(void);
        /**
         * @brief Notifies the observer about the image loading status
         */
        void RunL(void);
    private:
        /**
         * Initializes the path upon which the loader will work
         *
         * @param[in] aImgTwipSize desired image size in twips
         * @param     aObserver    object to receive image loading completion
         *                         notifications
         */
        CslideShowImgLoader(const TSize& aImgTwipSize,
            MslideShowImgLoadClient& aObserver);
        /**
         * @brief Second phase leaving constructor
         */
        void ConstructL(void);
        /**
         * @brief Cleans up a single image loading request
         */
        void EndLoad(void);
        /**
         * @brief Filesystem session
         */
        RFs iFilesys;
        /**
         * @brief Image loading and decoding facility
         */
        CImageDecoder* iImgLoader;
        /**
        * @brief Image object to store the loaded image in
        */
        CFbsBitmap* iImgObj;
        /**
         * @brief object to receive image loading completion notifications
         */
        MslideShowImgLoadClient& iObserver;
        /**
         * @brief Image size in twips
         */
        TSize iImgTwipSize;
        };

    }

#endif /* CSLIDESHOWIMGLOADER_H_ */
