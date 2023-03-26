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

}  // namespace sead
