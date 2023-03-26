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

private:
    TreeNode mTreeNode;
    FixedSafeString<0x40> mString;
    u8* mContent;
    u32 _88;
    bool _8C;
    u32 _90;
    ObjList<void*> mAttributes;
    Heap* mHeap;
};

}  // namespace sead