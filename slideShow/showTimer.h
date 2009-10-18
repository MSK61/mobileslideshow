#include "platformUtils.h"
namespace Slideshow
{
    /**
    * @brief Current bitmap to be displayed
    */
    extern std::list< tstring >::const_iterator curBitmap;
    /**
    * @brief Last bitmap to be displayed(one past the end)
    */
    extern std::list< tstring >::const_iterator lastBitmap;
    /**
    * @brief Current image object handle
    *
    * The image object should be reclaimed by the user code.
    */
    extern HBITMAP curImgObj;
    /**
    * @brief Handle of the original object of the in-memory device context
    *
    * The initial object should be restored by the user code.
    */
    extern HGDIOBJ initialDCObj;
    /**
    * @brief In-memory device context storing the bitmap
    *
    * The device context should be reclaimed by the user code.
    */
    extern HDC inMemDC;
    /**
    * @brief Image displaying timer callback
    *
    * @param[in] hwnd	 handle to the window associated with the timer
    * @param[in] uMsg    message type identifier
    * @param[in] idEvent timer identifier
    * @param[in] dwTime  number of milliseconds that have elapsed since the
	*                    system was started
    */
	void CALLBACK ChangeImg(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);
}
