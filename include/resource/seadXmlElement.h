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
        XmlAttribute(Heap* heap, const SafeString& name_, const SafeString& value_)
            : name(heap, name_), value(heap, value_)
        {
        }

        HeapSafeString name;
        HeapSafeString value;
    };

    enum class ContentType
    {
        TextMaybe,  // TODO
        CData,
        Base64,
    };

    XmlElement();

    virtual ~XmlElement();

    void setContent(u8* content, u32 content_length, bool owns_content);
    SafeString findAttributeValue(const SafeString& name) const;
    ObjList<XmlAttribute>* expandAttributeList(int capacity, Heap* heap);
    bool addAttribute(const SafeString& name, const SafeString& value, Heap* heap);
    bool updateAttribute(const SafeString& name, const SafeString& value, Heap* heap);
    SafeString getContentString() const;
    void setContentString(const SafeString& content, Heap* heap);

private:
    TreeNode mTreeNode{};
    FixedSafeString<0x40> mString = FixedSafeString<0x40>::cEmptyString;
    u8* mContent{};
    u32 mContentLength{};
    bool mOwnsContent{};
    ContentType mContentType = ContentType::TextMaybe;
    ObjList<XmlAttribute> mAttributes{};
    Heap* mHeap{};
};

}  // namespace sead