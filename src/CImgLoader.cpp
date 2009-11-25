/*
========================================================================
 Name        : CImgLoader.cpp
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

 Description : represents the implementation of the class CImgLoader
========================================================================
*/
#include "CImgLoader.h"
#include <imageconversion.h>
#include "MImgLoadClient.h"
namespace Slideshow
    {
    CImgLoader::CImgLoader(MImgLoadClient& aObserver) :
        CActive(EPriorityStandard), iImgObj(NULL), iImgLoader(NULL), iObserver(
            aObserver)
        {
        }

    void CImgLoader::LoadImgL(const TFileName& aFileName)
        {

        iImgLoader = CImageDecoder::FileNewL(iFilesys, aFileName);
        iImgObj = new (ELeave) CFbsBitmap;
        const TFrameInfo* const imgInfo = &(iImgLoader->FrameInfo());
        iImgObj->Create(imgInfo->iOverallSizeInPixels,
            imgInfo->iFrameDisplayMode);
        iImgLoader->Convert(&iStatus, *iImgObj);
        SetActive();

        }

    void CImgLoader::DoCancel(void)
        {

        if (iImgLoader != NULL)
            {

            iImgLoader->Cancel();
            EndLoad();
            delete iImgObj;
            iImgObj = NULL;

            }

        }

    void CImgLoader::RunL(void)
        {

        EndLoad();
        // Transfer the image ownership to the observer.
        iObserver.HandleImg(iStatus.Int(), iImgObj);
        iImgObj = NULL;

        }

    void CImgLoader::EndLoad(void)
        {

        delete iImgLoader;
        iImgLoader = NULL;

        }
    }
