HttpHeader::operator =(const HttpHeader &other)
{
    if (this != &other) {

        assert(owner == other.owner);
        clean();
        update(&other);
        len = other.len;
        conflictingContentLength_ = other.conflictingContentLength_;
        teUnsupported_ = other.teUnsupported_;
    }
    return *this;
}
