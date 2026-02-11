ConvertNetworkOrder (void* buffer, size_t bytes)
{
#ifndef WORDS_BIGENDIAN
    if (bytes < 2)
        return;

    char* start = static_cast<char*>(buffer);
    char* end = start + bytes - 1;
    size_t nSwap = bytes / 2;

    while (nSwap-- > 0) {
        unsigned char c = *start;
        *start++ = *end;
        *end-- = c;
    }
#endif
}
