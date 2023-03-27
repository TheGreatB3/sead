#include <algorithm>
#include <cstring>
#include <resource/seadXmlElement.h>

namespace sead
{

XmlElement::XmlElement() = default;

XmlElement::~XmlElement() = default;

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

void XmlElement::setContentString(const SafeString& content, Heap* heap)
{
    auto len = content.calcLength();
    auto* con = new (heap) u8[len + 1];

    memcpy(con, content.cstr(), len);
    con[len] = 0;

    setContent(con, len, true);
}

}  // namespace sead
