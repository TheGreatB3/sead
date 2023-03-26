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
    struct XmlAttribute
    {
    };

    enum class ContentType
    {
        TextMaybe,  // TODO
        CData,
        Base64,
    };

    XmlElement() = default;

    virtual ~XmlElement() = default;

private:
    TreeNode mTreeNode;
    FixedSafeString<0x40> mString;
    u8* mContent;
    u32 mContentLength;
    bool mOwnsContent;
    ContentType mContentType;
    ObjList<XmlAttribute> mAttributes;
    Heap* mHeap;
};

}  // namespace sead