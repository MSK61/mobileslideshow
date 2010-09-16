/*
========================================================================
 Name        : slideShowWnd.h
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
#ifndef SLIDESHOWWND_H
#define SLIDESHOWWND_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <coecntrl.h>
// ]]] end generated region [Generated Includes]

#include "MslideShowImgLoadClient.h"

// [[[ begin [Event Handler Includes]
// ]]] end [Event Handler Includes]

// [[[ begin generated region: do not modify [Generated Forward Declarations]
class MEikCommandObserver;
// ]]] end generated region [Generated Forward Declarations]

namespace Slideshow
{
class CslideShowImgLoader;
}
/**
 * Container class for slideShowWnd
 *
 * @class	CSlideShowWnd slideShowWnd.h
 */
class CSlideShowWnd : public CCoeControl,
    public Slideshow::MslideShowImgLoadClient
    {
public:
	// constructors and destructor
	CSlideShowWnd();
	static CSlideShowWnd* NewL(
		const TRect& aRect,
		const CCoeControl* aParent,
		MEikCommandObserver* aCommandObserver );
	static CSlideShowWnd* NewLC(
		const TRect& aRect,
		const CCoeControl* aParent,
		MEikCommandObserver* aCommandObserver );
	void ConstructL(
		const TRect& aRect,
		const CCoeControl* aParent,
		MEikCommandObserver* aCommandObserver );
	virtual ~CSlideShowWnd();

public:
	// from base class CCoeControl
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl( TInt aIndex ) const;
	TKeyResponse OfferKeyEventL(
			const TKeyEvent& aKeyEvent,
			TEventCode aType );
	void HandleResourceChange( TInt aType );

public:
    // from base class Slideshow::MslideShowImgLoadClient
    void HandleImg(TInt aLoadRes, const CFbsBitmap& aImgObj);

protected:
	// from base class CCoeControl
	void SizeChanged();

private:
	// from base class CCoeControl
	void Draw( const TRect& aRect ) const;

private:
    /**
     * @brief Exits the application
     */
    void ExitApp(void);
	void InitializeControlsL();
	void LayoutControls();
	/**
	 * @brief List of bitmap files to display
	 */
	CDir* iBmpFiles;
    /**
    * @brief Current bitmap to be displayed
    */
    TInt iCurBitmap;
	CCoeControl* iFocusControl;
	MEikCommandObserver* iCommandObserver;
	/**
	 * @brief Image loading and decoding facility
	 */
	Slideshow::CslideShowImgLoader* iImgLoader;
    /**
    * @brief In-memory device context storing the bitmap
    */
	CBitmapContext* iInMemDC;
	/**
	 * @brief Folder selected by the user
	 */
	TPath iSelFolder;
	/**
	 * @brief Image object to be displayed
	 */
	CWsBitmap* iShowImg;
	/**
	 * @brief Timer to trigger changing images
	 */
	CPeriodic* iTimer;
	// [[[ begin generated region: do not modify [Generated Methods]
public:
	// ]]] end generated region [Generated Methods]

	// [[[ begin generated region: do not modify [Generated Type Declarations]
public:
	// ]]] end generated region [Generated Type Declarations]

	// [[[ begin generated region: do not modify [Generated Instance Variables]
private:
	// ]]] end generated region [Generated Instance Variables]


	// [[[ begin [Overridden Methods]
protected:
	// ]]] end [Overridden Methods]


	// [[[ begin [User Handlers]
protected:
	// ]]] end [User Handlers]

public:
	enum TControls
		{
		// [[[ begin generated region: do not modify [Generated Contents]

		// ]]] end generated region [Generated Contents]

		// add any user-defined entries here...

		ELastControl
		};
    /**
     * @brief Image displaying timer callback
     */
    void ChangeImgL(void);
	};

#endif // SLIDESHOWWND_H
