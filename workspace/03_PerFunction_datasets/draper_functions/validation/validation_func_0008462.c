recvString(size_t maxlen)
{
    uint16_t size;
    if (recv(&size, sizeof(uint16_t)) <= 0)
        size = 0;
    if (size >= maxlen)
        size = maxlen-1;

    if (size > 0) {
        pl_wchar_t* buf = new pl_wchar_t[size];
        recv(buf, size * sizeof(pl_wchar_t));
        plString str(buf, size);
        delete[] buf;
        return str;
    } else {
        return plString();
    }
}
