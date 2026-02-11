parse_str(const char* buf, const char* tag, string& dest) {
    char tempbuf[1024];
    if (!parse_str(buf, tag, tempbuf, 1024)) return false;
    dest = tempbuf;
    return true;
}
