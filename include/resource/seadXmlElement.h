#pragma once

#include <container/seadObjList.h>
#include <container/seadTreeNode.h>
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
    TreeNode tree_node;
    FixedSafeString<0x40> string;
    u64 _80;
    u32 _88;
    bool _8C;
    u32 _90;
    ObjList<void*> attributes;
    u64 _C8;
};

}  // namespace sead