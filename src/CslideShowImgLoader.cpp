/*
 ========================================================================
 Name        : CslideShowImgLoader.cpp
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

 Description : represents the implementation of the class CslideShowImgLoader
 ========================================================================
 */

#include "../inc/CslideShowImgLoader.h"
#include <imageconversion.h>
#include "MslideShowImgLoadClient.h"

namespace Slideshow
    {

    CslideShowImgLoader::~CslideShowImgLoader()
        {

        delete iImgObj;

        }

    void CslideShowImgLoader::LoadImgL(const TFileName& aFileName)
        {

        iImgLoader = CImageDecoder::FileNewL(iFilesys, aFileName);
        const TFrameInfo* const imgInfo = &(iImgLoader->FrameInfo());
        User::LeaveIfError(iImgObj->Create(imgInfo->iOverallSizeInPixels,
            imgInfo->iFrameDisplayMode));
        iImgLoader->Convert(&iStatus, *iImgObj);
        SetActive();

        }

    CslideShowImgLoader* const CslideShowImgLoader::NewL(
        const TSize& aImgTwipSize, MslideShowImgLoadClient& aObserver)
        {
        CslideShowImgLoader* const self = new (ELeave) CslideShowImgLoader(
            aImgTwipSize, aObserver);

        CleanupStack::PushL(self);
        self->ConstructL();
        CleanupStack::Pop();// for the created image loader instance
        return self;

        }

    void CslideShowImgLoader::DoCancel(void)
        {

        if (iImgLoader != NULL)
            {

            iImgLoader->Cancel();
            EndLoad();

            }

        }

    void CslideShowImgLoader::RunL(void)
        {

        iImgObj->SetSizeInTwips(iImgTwipSize);//pre-notification processing
        iObserver.HandleImg(iStatus.Int(), *iImgObj);
        EndLoad();

        }

    CslideShowImgLoader::CslideShowImgLoader(const TSize& aImgTwipSize,
        MslideShowImgLoadClient& aObserver) :
        CActive(EPriorityStandard), iImgLoader(NULL), iImgObj(NULL),
        iObserver(aObserver), iImgTwipSize(aImgTwipSize)
        {
        }

    void CslideShowImgLoader::ConstructL(void)
        {

        iImgObj = new (ELeave) CFbsBitmap;

        }

    void CslideShowImgLoader::EndLoad(void)
        {

        delete iImgLoader;
        iImgLoader = NULL;
        iImgObj->Reset();

        }

    }
