#include <algorithm>
#include <prim/seadMemUtil.h>
#include <resource/seadXmlElement.h>

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
