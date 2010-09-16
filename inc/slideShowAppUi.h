/*
========================================================================
 Name        : slideShowAppUi.h
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
#ifndef SLIDESHOWAPPUI_H
#define SLIDESHOWAPPUI_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <aknappui.h>
#include <eikmenub.h>
// ]]] end generated region [Generated Includes]

// [[[ begin generated region: do not modify [Generated Forward Declarations]
class CSlideShowWnd;
// ]]] end generated region [Generated Forward Declarations]

/**
 * @class	CslideShowAppUi slideShowAppUi.h
 * @brief The AppUi class handles application-wide aspects of the user interface, including
 *        container management and the default menu, control pane, and status pane.
 */
class CslideShowAppUi : public CAknAppUi
	{
public:
	// constructor and destructor
	CslideShowAppUi();
	void ConstructL();
	virtual ~CslideShowAppUi();

public:
	// from CEikAppUi
	void HandleCommandL( TInt aCommand );
	void HandleResourceChangeL( TInt aType );

private:
	void InitializeContainersL();
	// [[[ begin generated region: do not modify [Generated Methods]
public:
	// ]]] end generated region [Generated Methods]

	// [[[ begin generated region: do not modify [Generated Instance Variables]
private:
	CSlideShowWnd* iSlideShowWnd;
	// ]]] end generated region [Generated Instance Variables]


	// [[[ begin [Overridden Methods]
protected:
	// ]]] end [Overridden Methods]


	// [[[ begin [User Handlers]
protected:
	// ]]] end [User Handlers]

	};

#endif // SLIDESHOWAPPUI_H
