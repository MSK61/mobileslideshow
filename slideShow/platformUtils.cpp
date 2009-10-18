#include "stdafx.h"
#include "PlatformUtils.h"
namespace Slideshow
{
    using std::list;
    const tstring pathSep = _T("\\");
    const list< tstring > GetContents(const tstring& dirName,
        const tstring& pattern, const DWORD attrFilter) throw ()
    {
        WIN32_FIND_DATA itemInfo;
        const HANDLE itemIter =
            FindFirstFile((dirName + pathSep + pattern).c_str(), &itemInfo);
        list< tstring > contents;

        if (itemIter != INVALID_HANDLE_VALUE)
        {

            /// Add contents matching the provided filter only.
            do if ((itemInfo.dwFileAttributes & attrFilter) == attrFilter)
                contents.push_back(itemInfo.cFileName);
            while (FindNextFile(itemIter, &itemInfo));

            FindClose(itemIter);

        }

        return contents;

    }
}
