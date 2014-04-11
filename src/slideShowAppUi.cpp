/*
========================================================================
 Name        : slideShowAppUi.cpp
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

 Description :
========================================================================
*/
// [[[ begin generated region: do not modify [Generated System Includes]
#include <eikmenub.h>
#include <akncontext.h>
#include <akntitle.h>
#include <slideShow.rsg>
// ]]] end generated region [Generated System Includes]

// [[[ begin generated region: do not modify [Generated User Includes]
#include "slideShowAppUi.h"
#include "slideShowWnd.h"
// ]]] end generated region [Generated User Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

/**
 * Construct the CslideShowAppUi instance
 */
CslideShowAppUi::CslideShowAppUi()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	iSlideShowWnd = NULL;
	// ]]] end generated region [Generated Contents]

	}

/**
 * The appui's destructor removes the container from the control
 * stack and destroys it.
 */
CslideShowAppUi::~CslideShowAppUi()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	if ( iSlideShowWnd != NULL )
		{
		RemoveFromStack( iSlideShowWnd );
		delete iSlideShowWnd;
		iSlideShowWnd = NULL;
		}
	// ]]] end generated region [Generated Contents]

	}

/**
 * @brief Completes the second phase of Symbian object construction.
 * Put initialization code that could leave here.
 */
void CslideShowAppUi::ConstructL()
	{
	// [[[ begin generated region: do not modify [Generated Contents]

	BaseConstructL( EAknEnableSkin  |
					 EAknEnableMSK );
	InitializeContainersL();
	// ]]] end generated region [Generated Contents]

	}

// [[[ begin generated function: do not modify
void CslideShowAppUi::InitializeContainersL()
	{
	iSlideShowWnd = CSlideShowWnd::NewL( ClientRect(), NULL, this );
	iSlideShowWnd->SetMopParent( this );
	AddToStackL( iSlideShowWnd );
	}
// ]]] end generated function

/**
 * Handle a command for this appui (override)
 * @param aCommand command id to be handled
 */
void CslideShowAppUi::HandleCommandL( TInt aCommand )
	{
	// [[[ begin generated region: do not modify [Generated Code]
	TBool commandHandled = EFalse;
	switch ( aCommand )
		{ // code to dispatch to the AppUi's menu and CBA commands is generated here
		default:
			break;
		}


	if ( !commandHandled )
		{
		if ( aCommand == EAknSoftkeyExit || aCommand == EEikCmdExit )
			{
			Exit();
			}
		}
	// ]]] end generated region [Generated Code]

	}

/**
 * Override of the HandleResourceChangeL virtual function
 */
void CslideShowAppUi::HandleResourceChangeL( TInt aType )
	{
	CAknAppUi::HandleResourceChangeL( aType );
	// [[[ begin generated region: do not modify [Generated Code]
	// ]]] end generated region [Generated Code]

	}

