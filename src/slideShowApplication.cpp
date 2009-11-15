/*
========================================================================
 Name        : slideShowApplication.cpp
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

 Description : 
========================================================================
*/
// [[[ begin generated region: do not modify [Generated System Includes]
// ]]] end generated region [Generated System Includes]

// [[[ begin generated region: do not modify [Generated Includes]
#include "slideShowApplication.h"
#include "slideShowDocument.h"
#ifdef EKA2
#include <eikstart.h>
#endif
// ]]] end generated region [Generated Includes]

/**
 * @brief Returns the application's UID (override from CApaApplication::AppDllUid())
 * @return UID for this application (KUidslideShowApplication)
 */
TUid CslideShowApplication::AppDllUid() const
	{
	return KUidslideShowApplication;
	}

/**
 * @brief Creates the application's document (override from CApaApplication::CreateDocumentL())
 * @return Pointer to the created document object (CslideShowDocument)
 */
CApaDocument* CslideShowApplication::CreateDocumentL()
	{
	return CslideShowDocument::NewL( *this );
	}

#ifdef EKA2

/**
 *	@brief Called by the application framework to construct the application object
 *  @return The application (CslideShowApplication)
 */	
LOCAL_C CApaApplication* NewApplication()
	{
	return new CslideShowApplication;
	}

/**
* @brief This standard export is the entry point for all Series 60 applications
* @return error code
 */	
GLDEF_C TInt E32Main()
	{
	return EikStart::RunApplication( NewApplication );
	}
	
#else 	// Series 60 2.x main DLL program code

/**
* @brief This standard export constructs the application object.
* @return The application (CslideShowApplication)
*/
EXPORT_C CApaApplication* NewApplication()
	{
	return new CslideShowApplication;
	}

/**
* @brief This standard export is the entry point for all Series 60 applications
* @return error code
*/
GLDEF_C TInt E32Dll(TDllReason /*reason*/)
	{
	return KErrNone;
	}

#endif // EKA2
