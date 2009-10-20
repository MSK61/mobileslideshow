/************************************************************
 *
 * Copyright 2009 Mohammed El-Afifi
 * This file is part of slideShow.
 *
 * slideShow is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * slideShow is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with slideShow.  If not, see <http://www.gnu.org/licenses/>.
 *
 * file:         dirDlg.cpp
 *
 * function:	 GetFullPath, GetNodes, GetSubdirs, HandleCtrlMsg, UpdateNode,
 *				 and DirDlgProc
 *
 * description:  runtime logic of the folder browse dialog box
 *
 * author:       Mohammed Safwat (MS)
 *
 * environment:  Microsoft Visual C++ 2008, Windows Mobile 6 Professional SDK,
 *				 windows xp profesional
 *
 * notes:        This is a private program.
 *
 ************************************************************/
#include "stdafx.h"
#include "dirDlg.h"
#include "resourcesp.h"
using std::list;
namespace {
    using namespace Slideshow;
    /**
    * @brief Retrieves the text of the tree node with the specified handle
    *
    * @param[in] treeID ID of the tree containing the node
    * @param[in] itemID ID of the node to be retrieved
    * @return           text of the requested tree node
    */
    const tstring GetNodeText(const HWND treeID, const HTREEITEM itemID)
        throw ();
    /**
    * @brief Updates the specified tree node
    *
    * The function either adds the nodes as children to the given node, or marks
    * the node as having no children.
    *
    * @param[in] treeID   ID of the tree containing the node
    * @param[in] parentID ID of the node to be updated
    */
    void UpdateNode(const HWND treeID, HTREEITEM parentID) throw ();
    /**
    * @brief Returns the full path of the given tree node
    *
    * @param[in] treeID ID of the tree containing the node
    * @param[in] itemID ID of the node to construct its full path
    * return            the full path of the given node
    */
    const tstring GetFullPath(const HWND treeID, HTREEITEM itemID) throw ()
    {
        tstring fullPath = _T("");

        while (itemID != NULL && itemID != TVI_ROOT)
        {

            /// Prepend the full path with the current parent text.
            fullPath = pathSep + GetNodeText(treeID, itemID) + fullPath;
            itemID = TreeView_GetParent(treeID, itemID);

        }

        return fullPath;

    }

    const tstring GetNodeText(const HWND treeID, const HTREEITEM itemID)
        throw ()
    {
        TVITEM itemNode;
        static const int maxTextLen = 261;// including the null terminator
        TCHAR txtBuf[maxTextLen];

        itemNode.hItem = itemID;
        itemNode.cchTextMax = maxTextLen;
        itemNode.pszText = txtBuf;
        itemNode.mask = TVIF_TEXT;
        TreeView_GetItem(treeID, &itemNode);
        return txtBuf;

    }

    /**
    * @brief Returns the subdirectories under the given directory
    *
    * @param[in] dirName directory to return its subdirectories
    * return             subdirectories of the given directory
    */
    const list< tstring > GetSubdirs(const tstring& dirName) throw ()
    {
        // subdirectory conditions
        static const TCHAR allPattern[] = _T("*");
        static const DWORD dirFilter = FILE_ATTRIBUTE_DIRECTORY;

        return GetContents(dirName, allPattern, dirFilter);

    }

    /**
    * @brief Processes messages directed to controls inside the directory
    *        selection dialog box
    *
    * @param[in] dlgHandle handle to the dialog box
    * @param[in] msgID     message type identifier
    * @param[in] wParam    message-specific parameters
    * @param[in] lParam    message-specific parameters
    * @return              true if the message gets processed, otherwise false
    */
    const INT_PTR HandleCtrlMsg(
        HWND dlgHandle, UINT msgID, WPARAM wParam, LPARAM lParam) throw ()
    {
        LPNMTREEVIEW notifyInfo = NULL;
        const HWND treeID = GetDlgItem(dlgHandle, IDC_DIR_TREE);

        switch (msgID)
        {

        case WM_COMMAND:

            switch (LOWORD(wParam))
            {

            case IDC_OK:// OK button

                Slideshow::browseDirName =
                    GetFullPath(treeID, TreeView_GetSelection(treeID));
                EndDialog(dlgHandle, 0);
                break;

            default:// no-op

                return FALSE;

            }

            break;

        case WM_NOTIFY:// node expansion events

            if (LPNMHDR(lParam) -> code == TVN_ITEMEXPANDING)
            {

                notifyInfo = LPNMTREEVIEW(lParam);

                if (notifyInfo -> action == TVE_EXPAND &&
                    (notifyInfo -> itemNew.state & TVIS_EXPANDEDONCE) == 0)
                    UpdateNode(treeID, notifyInfo -> itemNew.hItem);

            }

            break;

        default:// no-op

            return FALSE;

        }

        return TRUE;

    }

    void UpdateNode(const HWND treeID, HTREEITEM parentID) throw ()
    {
        const list< tstring > children =
            GetSubdirs(GetFullPath(treeID, parentID));
        list< tstring >::const_iterator curChild;
        tstring::size_type dirNameLen;
        // node children flags
        static const int hasChildren = 1;
        static const int noChildren = 0;
        const list< tstring >::const_iterator lastChild = children.end();
        TV_INSERTSTRUCT newItem;
        const bool nonRootParent = parentID != NULL && parentID != TVI_ROOT;
        TVITEM parent;

        parent.pszText = NULL;
        newItem.item.pszText = NULL;

        if (!children.empty())/// Append children nodes to the parent node.
        {

            newItem.hParent = parentID;
            newItem.hInsertAfter = TVI_LAST;
            newItem.item.cChildren = hasChildren;
            newItem.item.mask = TVIF_CHILDREN | TVIF_TEXT;

            for (curChild = children.begin(); curChild != lastChild; curChild++)
            {

                dirNameLen = curChild -> size() + 1;
                newItem.item.pszText = new TCHAR[dirNameLen];
                StringCchCopy(
                    newItem.item.pszText, dirNameLen, (*curChild).c_str());
                TreeView_InsertItem(treeID, &newItem);
                // memory clean-up
                delete []newItem.item.pszText;
                newItem.item.pszText = NULL;

            }

        }
        /// Update the GUI for non-root nodes having no children.
        else if (nonRootParent)
        {

            parent.hItem = parentID;
            parent.cChildren = noChildren;
            parent.mask = TVIF_CHILDREN;
            TreeView_SetItem(treeID, &parent);

        }

    }
}
namespace Slideshow
{
    tstring browseDirName;
    INT_PTR CALLBACK DirDlgProc(
        HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {

        switch (uMsg)
        {

        case WM_INITDIALOG:

            // Publish the store names as root nodes.
            UpdateNode(GetDlgItem(hwndDlg, IDC_DIR_TREE), TVI_ROOT);
            break;

        default:// no-op

            return HandleCtrlMsg(hwndDlg, uMsg, wParam, lParam);

        }

        return TRUE;

    }
}
