inline bool compare(const char* str, const Exiv2::DataBuf& buf, size_t length)
    {

        assert(strlen(str) <= length);
        return memcmp(str, buf.pData_, std::min(length, buf.size_)) == 0;
    }
