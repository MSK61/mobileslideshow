#include "stdafx.h"
#include "showTimer.h"
namespace Slideshow
{
    using std::list;
    list< tstring >::const_iterator curBitmap;
    list< tstring >::const_iterator lastBitmap;
    HBITMAP curImgObj = NULL;
    HGDIOBJ initialDCObj = NULL;
    HDC inMemDC = NULL;
    void CALLBACK ChangeImg(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
    {
        RECT clientRect;
        HGDIOBJ oldImgObj;

        if (curBitmap == lastBitmap) DestroyWindow(hwnd);// end of image list
        else
        {

            /// Create a device context if no one already exists.
            if (inMemDC == NULL) inMemDC = CreateCompatibleDC(NULL);

            /// Load the current bitmap and associate it to the device context.
            curImgObj = SHLoadDIBitmap(curBitmap++ -> c_str());
            oldImgObj = SelectObject(inMemDC, curImgObj);

            if (inMemDC == NULL || curImgObj == NULL || oldImgObj == NULL)
                DestroyWindow(hwnd);/// Trap errors.

            // Maintain/clean up old data.
            if (initialDCObj == NULL) initialDCObj = oldImgObj;
            else DeleteObject(oldImgObj);

            /// Invalidate all the client area.
            GetClientRect(hwnd, &clientRect);
            InvalidateRect(hwnd, &clientRect, FALSE);

        }

    }
}
