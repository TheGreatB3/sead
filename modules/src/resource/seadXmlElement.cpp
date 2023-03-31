#include <algorithm>
#include <container/seadObjArray.h>
#include <prim/seadMemUtil.h>
#include <resource/seadXmlElement.h>
#include <utility>

namespace sead
{

XmlElement::XmlElement() = default;

XmlElement::~XmlElement()
{
    if (mContent && mOwnsContent)
    {
        delete[] mContent;
    }

    mAttributes.freeBuffer();
}

void XmlElement::setContent(u8* content, u32 content_length, bool owns_content)
{
    if (mContent != content)
    {
        if (mContent && mOwnsContent)
        {
            delete[] mContent;
        }

        mOwnsContent = owns_content;
        mContent = content;
        mContentLength = content_length;
    }
}

SafeString XmlElement::findAttributeValue(const SafeString& name) const
{
    for (const auto& attr : mAttributes)
    {
        if (attr.name == name)
        {
            return attr.value;
        }
    }

    return SafeString::cEmptyString;
}

// NON_MATCHING
ObjList<XmlElement::XmlAttribute>* XmlElement::expandAttributeList(int capacity, Heap* heap)
{
    if (!heap)
        heap = mHeap;

    if (!mAttributes.isBufferReady())
    {
        mAttributes.allocBuffer(capacity, heap);
        return &mAttributes;
    }

    s32 size = mAttributes.size();
    if (size >= capacity)
        return &mAttributes;

    {
        ObjArray<std::pair<FixedSafeString<0x400>, FixedSafeString<0x400>>> temp_values{};
        temp_values.allocBuffer(size, heap, -8);  // Not sure why alignment is negative.

        for (const auto& attr : mAttributes)
        {
            auto* temp_value = temp_values.emplaceBack(FixedSafeString<0x400>::cEmptyString,
                                                       FixedSafeString<0x400>::cEmptyString);
            temp_value->first = attr.name;
            temp_value->second = attr.value;
        }

        mAttributes.freeBuffer();

        mAttributes.allocBuffer(capacity, heap);

        for (const auto& [name, value] : temp_values)
        {
            mAttributes.emplaceBack(heap, name, value);
        }

        temp_values.freeBuffer();
    }

    return &mAttributes;
}

bool XmlElement::addAttribute(const SafeString& name, const SafeString& value, Heap* heap)
{
    if (name.isEmpty() || !mAttributes.isBufferReady() || mAttributes.isFull())
        return false;

    for (const auto& attr : mAttributes)
    {
        if (name == attr.name)
            return false;
    }

    mAttributes.emplaceBack(heap, name, value);
    return true;
}

// NON_MATCHING
bool XmlElement::updateAttribute(const SafeString& name, const SafeString& value, Heap* heap)
{
    if (mAttributes.isEmpty())
        return false;

    for (auto& attr : mAttributes)
    {
        if (name == attr.name)
        {
            // if (value != attr.value)
            {
                auto valueLen = value.calcLength();
                if (valueLen <= attr.value.calcLength())
                {
                    attr.value.cutOffCopy(value, valueLen);
                }
                else
                {
                    mAttributes.erase(&attr);
                    addAttribute(name, value, heap);
                }
            }
            return true;
        }
    }

    return false;
}

SafeString XmlElement::getContentString() const
{
    return mContent ? SafeString{(const char*)mContent} : SafeString::cEmptyString;
}

void XmlElement::setContentString(const SafeString& content, Heap* heap)
{
    auto len = content.calcLength();
    auto* con = new (heap) u8[len + 1];

    MemUtil::copy(con, content.cstr(), len);
    con[len] = 0;

    setContent(con, len, true);
}

}  // namespace sead
