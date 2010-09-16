/*
========================================================================
 Name        : slideShowDocument.cpp
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
// [[[ begin generated region: do not modify [Generated User Includes]
#include "slideShowDocument.h"
#include "slideShowAppUi.h"
// ]]] end generated region [Generated User Includes]

/**
 * @brief Constructs the document class for the application.
 * @param anApplication the application instance
 */
CslideShowDocument::CslideShowDocument( CEikApplication& anApplication )
	: CAknDocument( anApplication )
	{
	}

/**
 * @brief Completes the second phase of Symbian object construction. 
 * Put initialization code that could leave here.  
 */ 
void CslideShowDocument::ConstructL()
	{
	}
	
/**
 * Symbian OS two-phase constructor.
 *
 * Creates an instance of CslideShowDocument, constructs it, and
 * returns it.
 *
 * @param aApp the application instance
 * @return the new CslideShowDocument
 */
CslideShowDocument* CslideShowDocument::NewL( CEikApplication& aApp )
	{
	CslideShowDocument* self = new ( ELeave ) CslideShowDocument( aApp );
	CleanupStack::PushL( self );
	self->ConstructL();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * @brief Creates the application UI object for this document.
 * @return the new instance
 */	
CEikAppUi* CslideShowDocument::CreateAppUiL()
	{
	return new ( ELeave ) CslideShowAppUi;
	}
				
