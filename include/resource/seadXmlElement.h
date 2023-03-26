#pragma once

#include <container/seadObjList.h>
#include <container/seadTreeNode.h>
#include <heap/seadHeap.h>
#include <prim/seadSafeString.h>

namespace sead
{

class XmlElement
{
public:
    XmlElement() = default;

    virtual ~XmlElement() = default;

    struct XmlAttribute
    {
    };

    enum class ContentType
    {
        TextMaybe,  // TODO
        CData,
        Base64,
    };

private:
    TreeNode mTreeNode;
    FixedSafeString<0x40> mString;
    u8* mContent;
    u32 mContentLength;
    bool mOwnsContent;
    ContentType mContentType;
    ObjList<void*> mAttributes;
    Heap* mHeap;
};

}  // namespace sead