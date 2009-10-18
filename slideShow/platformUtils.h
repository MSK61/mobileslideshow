#include <list>
#include <string>
#include <WinDef.h>
#ifdef _UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif
namespace Slideshow
{
    /**
    * @brief Path separator
    */
    extern const tstring pathSep;
    /**
    * @brief Returns the contents of the given directory with the specified
    * conditions
    *
    * @param[in] dirName	directory to return its contents
    * @param[in] pattern	pattern to filter contents
    * @param[in] attrFilter attributes to match with contents
    * return				contents of the given directory matching the
    *						specified conditions
    */
    const std::list< tstring > GetContents(const tstring& dirName,
        const tstring& pattern, const DWORD attrFilter) throw ();
}
