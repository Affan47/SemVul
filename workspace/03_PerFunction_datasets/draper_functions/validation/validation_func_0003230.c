CheckSGFVersion(const char **sz)
{

    int n;
    static int ver = 0;
    char *pch = strstr(*sz, "ver");
    if ((pch == 0) || (sscanf(pch, "ver %d", &n) != 1))
        return ver;
    ver = n;

    pch += 4;
    while (*pch != ' ') {
        ++pch;
    }
    *sz = pch;
    return ver;
}
