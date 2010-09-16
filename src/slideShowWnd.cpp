/*
========================================================================
 Name        : slideShowWnd.cpp
 Author      : Mohammed Safwat
 Copyright   : 2009, 2010 Mohammed El-Afifi
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

 Description :
========================================================================
*/
// [[[ begin generated region: do not modify [Generated System Includes]

#include <eikmenub.h>

#include <eikcmobs.h>
#include <eikappui.h>
#include <slideShow.rsg>
// ]]] end generated region [Generated System Includes]
#include <caknfileselectiondialog.h>
#include "CslideShowImgLoader.h"
#include <pathinfo.h>
#include <stringloader.h>

// [[[ begin generated region: do not modify [Generated User Includes]
#include "slideShowWnd.h"
#include "slideShowAppUi.h"
// ]]] end generated region [Generated User Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

namespace
    {
    /**
     * @brief Image displaying timer callback
     *
     * @param aPtr view to receive the timer event notification
     */
    TInt FlipImgL(TAny* aPtr)
        {

        ((CSlideShowWnd*) aPtr)->ChangeImgL();
        return 0;

        }
    }
/**
 * First phase of Symbian two-phase construction. Should not
 * contain any code that could leave.
 */
CSlideShowWnd::CSlideShowWnd() :
    iBmpFiles(NULL), iImgLoader(NULL), iInMemDC(NULL), iShowImg(NULL)
    {
    // [[[ begin generated region: do not modify [Generated Contents]
    // ]]] end generated region [Generated Contents]

    }
/**
 * Destroy child controls.
 */
CSlideShowWnd::~CSlideShowWnd()
    {
    // [[[ begin generated region: do not modify [Generated Contents]
    // ]]] end generated region [Generated Contents]

    if (iTimer != NULL)
        {

        iTimer->Cancel();
        delete iTimer;

        }

    if (iImgLoader != NULL)
        {

        iImgLoader->Cancel();
        delete iImgLoader;

        }

    delete iBmpFiles;

    if (iInMemDC != NULL)
        {

        const CGraphicsDevice* const imgDev = iInMemDC->Device();
        delete iInMemDC;
        delete imgDev;

        }

    delete iShowImg;

    }

/**
 * Construct the control (first phase).
 *  Creates an instance and initializes it.
 *  Instance is not left on cleanup stack.
 * @param aRect bounding rectangle
 * @param aParent owning parent, or NULL
 * @param aCommandObserver command observer
 * @return initialized instance of CSlideShowWnd
 */
CSlideShowWnd* CSlideShowWnd::NewL(
		const TRect& aRect,
		const CCoeControl* aParent,
		MEikCommandObserver* aCommandObserver )
	{
	CSlideShowWnd* self = CSlideShowWnd::NewLC(
			aRect,
			aParent,
			aCommandObserver );
	CleanupStack::Pop( self );
	return self;
	}

/**
 * Construct the control (first phase).
 *  Creates an instance and initializes it.
 *  Instance is left on cleanup stack.
 * @param aRect The rectangle for this window
 * @param aParent owning parent, or NULL
 * @param aCommandObserver command observer
 * @return new instance of CSlideShowWnd
 */
CSlideShowWnd* CSlideShowWnd::NewLC(
		const TRect& aRect,
		const CCoeControl* aParent,
		MEikCommandObserver* aCommandObserver )
	{
	CSlideShowWnd* self = new ( ELeave ) CSlideShowWnd();
	CleanupStack::PushL( self );
	self->ConstructL( aRect, aParent, aCommandObserver );
	return self;
	}

/**
 * Construct the control (second phase).
 *  Creates a window to contain the controls and activates it.
 * @param aRect bounding rectangle
 * @param aCommandObserver command observer
 * @param aParent owning parent, or NULL
 */
void CSlideShowWnd::ConstructL(
		const TRect& aRect,
		const CCoeControl* aParent,
		MEikCommandObserver* aCommandObserver )
	{
	if ( aParent == NULL )
	    {
		CreateWindowL();
	    }
	else
	    {
	    SetContainerWindowL( *aParent );
	    }
	iFocusControl = NULL;
	iCommandObserver = aCommandObserver;
	InitializeControlsL();
    TSize x = aRect.Size();
	SetRect( aRect );
	ActivateL();
	// [[[ begin generated region: do not modify [Post-ActivateL initializations]
	// ]]] end generated region [Post-ActivateL initializations]
    CAknFileSelectionDialog* const browseDlg = CAknFileSelectionDialog::NewL(
        ECFDDialogTypeCopy);
    CleanupStack::PushL(browseDlg);
    /// Customize the folder selection dialog.
    TBuf<32> dlgTitle;
    StringLoader::Load(dlgTitle, R_BRWS_DLG_TITLE);
    browseDlg->SetTitleL(dlgTitle);
    TBuf<16> selBtn;
    StringLoader::Load(selBtn, R_BRWS_SEL_BTN);
    browseDlg->SetLeftSoftkeyFileL(selBtn);
    iSelFolder = PathInfo::PhoneMemoryRootPath();

    if (browseDlg->ExecuteL(iSelFolder))
        {

        RFs filesys;
        CleanupClosePushL(filesys);
        User::LeaveIfError(filesys.Connect());
        User::LeaveIfError(filesys.SetSessionPath(iSelFolder));
        _LIT(KBmpFilter, "*.bmp");
        User::LeaveIfError(filesys.GetDir(KBmpFilter, KEntryAttNormal,
            ESortNone, iBmpFiles));
        CleanupStack::PopAndDestroy();// for the filesystem session
        // Prepare the in-memory buffer.
        iShowImg = new (ELeave) CWsBitmap(iEikonEnv->WsSession());
        TSize rectSize = aRect.Size();
        User::LeaveIfError(iShowImg->Create(rectSize,
            iEikonEnv->ScreenDevice()->DisplayMode()));
        iShowImg->SetSizeInTwips(rectSize);
        CFbsBitmapDevice* const imgDev = CFbsBitmapDevice::NewL(iShowImg);
        CleanupStack::PushL(imgDev);
        User::LeaveIfError(imgDev->CreateBitmapContext(iInMemDC));
        CleanupStack::Pop();// for the image device
        iImgLoader = Slideshow::CslideShowImgLoader::NewL(rectSize, *this);
        iCurBitmap = 0;
        CActiveScheduler::Add(iImgLoader);
        iTimer = CPeriodic::NewL(CPeriodic::EPriorityStandard);
        ChangeImgL();

        }
    else
        ExitApp();

    CleanupStack::PopAndDestroy();// for the folder selection dialog

	}

/**
* Return the number of controls in the container (override)
* @return count
*/
TInt CSlideShowWnd::CountComponentControls() const
	{
	return ( int ) ELastControl;
	}

/**
* Get the control with the given index (override)
* @param aIndex Control index [0...n) (limited by #CountComponentControls)
* @return Pointer to control
*/
CCoeControl* CSlideShowWnd::ComponentControl( TInt aIndex ) const
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	switch ( aIndex )
		{
		}
	// ]]] end generated region [Generated Contents]

	// handle any user controls here...

	return NULL;
	}

/**
 *	Handle resizing of the container. This implementation will lay out
 *  full-sized controls like list boxes for any screen size, and will layout
 *  labels, editors, etc. to the size they were given in the UI designer.
 *  This code will need to be modified to adjust arbitrary controls to
 *  any screen size.
 */
void CSlideShowWnd::SizeChanged()
	{
	CCoeControl::SizeChanged();
	LayoutControls();
	// [[[ begin generated region: do not modify [Generated Contents]

	// ]]] end generated region [Generated Contents]

	}

// [[[ begin generated function: do not modify
/**
 * Layout components as specified in the UI Designer
 */
void CSlideShowWnd::LayoutControls()
	{
	}
// ]]] end generated function

/**
 *	Handle key events.
 */
TKeyResponse CSlideShowWnd::OfferKeyEventL(
		const TKeyEvent& aKeyEvent,
		TEventCode aType )
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]

	if ( iFocusControl != NULL
		&& iFocusControl->OfferKeyEventL( aKeyEvent, aType ) == EKeyWasConsumed )
		{
		return EKeyWasConsumed;
		}
	return CCoeControl::OfferKeyEventL( aKeyEvent, aType );
	}

void CSlideShowWnd::ExitApp(void)
    {

    iCommandObserver->ProcessCommandL(EAknSoftkeyExit);

    }

// [[[ begin generated function: do not modify
/**
 *	Initialize each control upon creation.
 */
void CSlideShowWnd::InitializeControlsL()
	{

	}
// ]]] end generated function

/**
 * Handle global resource changes, such as scalable UI or skin events (override)
 */
void CSlideShowWnd::HandleResourceChange( TInt aType )
	{
	CCoeControl::HandleResourceChange( aType );
	SetRect( static_cast< CEikAppUi* >( iCoeEnv->AppUi() )->ClientRect() );
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]

	}

void CSlideShowWnd::HandleImg(TInt aLoadRes, const CFbsBitmap& aImgObj)
    {

    if (aLoadRes == KErrNone)
        {

        iInMemDC->DrawBitmap(TPoint(0, 0), &aImgObj);
        DrawDeferred();
        static const TTimeIntervalMicroSeconds32 KTimerPeriod = 2000000;
        iTimer->Start(KTimerPeriod, KTimerPeriod, TCallBack(FlipImgL, this));

        }

    }

/**
 *	Draw container contents.
 */
void CSlideShowWnd::Draw( const TRect& aRect ) const
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	CWindowGc& gc = SystemGc();
	gc.Clear( aRect );

	// ]]] end generated region [Generated Contents]
	if (iShowImg != NULL)
        gc.BitBlt(aRect.iTl, iShowImg);

	}

void CSlideShowWnd::ChangeImgL(void)
    {

    if (iCurBitmap == iBmpFiles->Count()) ExitApp();// end of image list
    else
        {

        iTimer->Cancel();
        TFileName imgFile = iSelFolder;
        imgFile.Append((*iBmpFiles)[iCurBitmap++].iName);
        iImgLoader->LoadImgL(imgFile);

        }

    }

