/*
========================================================================
 Name        : slideShowDocument.h
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
#ifndef SLIDESHOWDOCUMENT_H
#define SLIDESHOWDOCUMENT_H

#include <akndoc.h>
		
class CEikAppUi;

/**
* @class	CslideShowDocument slideShowDocument.h
* @brief	A CAknDocument-derived class is required by the S60 application 
*           framework. It is responsible for creating the AppUi object. 
*/
class CslideShowDocument : public CAknDocument
	{
public: 
	// constructor
	static CslideShowDocument* NewL( CEikApplication& aApp );

private: 
	// constructors
	CslideShowDocument( CEikApplication& aApp );
	void ConstructL();
	
public: 
	// from base class CEikDocument
	CEikAppUi* CreateAppUiL();
	};
#endif // SLIDESHOWDOCUMENT_H
