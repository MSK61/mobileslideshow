
#ifndef SLIDESHOW_PAN_H
#define SLIDESHOW_PAN_H

/** slideShow application panic codes */
enum TslideShowPanics
	{
	EslideShowUi = 1
	// add further panics here
	};

inline void Panic(TslideShowPanics aReason)
	{
	_LIT(applicationName,"slideShow");
	User::Panic(applicationName, aReason);
	}

#endif // SLIDESHOW_PAN_H
