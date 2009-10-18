#include "platformUtils.h"
namespace Slideshow
{
    /**
    * @brief Directory selected by the directory selection dialog box
    */
    extern tstring browseDirName;
    /**
    * @brief Processes messages directed to the director selection dialog
    *
    * @param[in] hwndDlg handle to the dialog box
    * @param[in] uMsg    message type identifier
    * @param[in] wParam  message-specific parameters
    * @param[in] lParam  message-specific parameters
    * @return            true if the message gets processed, otherwise false
    */
    INT_PTR CALLBACK DirDlgProc(
        HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
}
