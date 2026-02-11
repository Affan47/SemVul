qfile_abspath(char *buf, size_t bufsize, const char *path) {
    if (bufsize == 0)
        return NULL;

    if (path[0] == '/') {
        qstrcpy(buf, bufsize, path);
    } else {
        if (getcwd(buf, bufsize) == NULL)
            return NULL;
        strcat(buf, "/");
        strcat(buf, path);
    }
    qfile_correct_path(buf);

    return buf;
}
