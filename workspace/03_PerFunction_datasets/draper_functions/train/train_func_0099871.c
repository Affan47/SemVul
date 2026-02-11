makeipaddr(struct sockaddr *addr, int addrlen)
{
    char buf[NI_MAXHOST];
    int error;

    error = getnameinfo(addr, addrlen, buf, sizeof(buf), NULL, 0,
        NI_NUMERICHOST);
    if (error) {
        set_gaierror(error);
        return NULL;
    }
    return PyUnicode_FromString(buf);
}
