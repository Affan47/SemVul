parent_dir (const char * path ) {
    int len, rootlen;

    len = strlen(path);
    rootlen = strlen(gjay->prefs->song_root_dir);
    if (len <= rootlen)
        return NULL;
    if (!len)
        return NULL;
    for (; len > rootlen; len--) {
        if (path[len] == '/') {
            return g_strndup(path, len);
        }
    }
    if (path[len - 1] == '/')
        len--;
    return g_strndup(path, len);
}
