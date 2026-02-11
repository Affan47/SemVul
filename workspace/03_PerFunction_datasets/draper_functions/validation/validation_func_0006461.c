anc_inspect_socket_rights(int level, int type, VALUE data, VALUE ret)
{
    if (level == SOL_SOCKET && type == SCM_RIGHTS &&
        0 < RSTRING_LEN(data) && (RSTRING_LEN(data) % sizeof(int) == 0)) {
        long off;
        for (off = 0; off < RSTRING_LEN(data); off += sizeof(int)) {
            int fd;
            memcpy((char*)&fd, RSTRING_PTR(data)+off, sizeof(int));
            rb_str_catf(ret, " %d", fd);
        }
        return 1;
    }
    else {
        return 0;
    }
}
