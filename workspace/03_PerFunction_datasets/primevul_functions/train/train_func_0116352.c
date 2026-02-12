__libxml2_xzdopen(int fd, const char *mode)
{
    char *path;
    xzFile xz;

    if (fd == -1 || (path = xmlMalloc(7 + 3 * sizeof(int))) == NULL)
        return NULL;
    sprintf(path, "<fd:%d>", fd);
    xz = xz_open(path, fd, mode);
    xmlFree(path);
    return xz;
}
