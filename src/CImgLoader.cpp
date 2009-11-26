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

#include "../inc/CImgLoader.h"
#include <imageconversion.h>
#include "MImgLoadClient.h"

namespace Slideshow
    {

    CImgLoader::~CImgLoader()
        {

        delete iImgObj;

        }

    void CImgLoader::LoadImgL(const TFileName& aFileName)
        {

        iImgLoader = CImageDecoder::FileNewL(iFilesys, aFileName);
        const TFrameInfo* const imgInfo = &(iImgLoader->FrameInfo());
        User::LeaveIfError(iImgObj->Create(imgInfo->iOverallSizeInPixels,
            imgInfo->iFrameDisplayMode));
        iImgLoader->Convert(&iStatus, *iImgObj);
        SetActive();

        }

    CImgLoader* const CImgLoader::NewL(const TSize& aImgTwipSize,
        MImgLoadClient& aObserver)
        {
        CImgLoader* const self = new (ELeave) CImgLoader(aImgTwipSize,
            aObserver);

        CleanupStack::PushL(self);
        self->ConstructL();
        CleanupStack::Pop();// for the created image loader instance
        return self;

        }

    void CImgLoader::DoCancel(void)
        {

        if (iImgLoader != NULL)
            {

            iImgLoader->Cancel();
            EndLoad();

            }

        }

    void CImgLoader::RunL(void)
        {

        iImgObj->SetSizeInTwips(iImgTwipSize);//pre-notification processing
        iObserver.HandleImg(iStatus.Int(), *iImgObj);
        EndLoad();

        }

    CImgLoader::CImgLoader(const TSize& aImgTwipSize, MImgLoadClient& aObserver) :
        CActive(EPriorityStandard),
            iImgLoader(NULL), iImgObj(NULL),
            iObserver(aObserver), iImgTwipSize(aImgTwipSize)
        {
        }

    void CImgLoader::ConstructL(void)
        {

        iImgObj = new (ELeave) CFbsBitmap;

        }

    void CImgLoader::EndLoad(void)
        {

        delete iImgLoader;
        iImgLoader = NULL;
        iImgObj->Reset();

        }

    }
