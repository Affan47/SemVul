static FILE *inc_fopen(const char *file,
                       struct strlist *dhead,
                       const char **found_path,
                       enum incopen_mode omode,
                       enum file_flags fmode)
{
    struct hash_insert hi;
    void **hp;
    char *path;
    FILE *fp = NULL;

    hp = hash_find(&FileHash, file, &hi);
    if (hp) {
        path = *hp;
        if (path || omode != INC_NEEDED) {
            strlist_add(dhead, path ? path : file);
        }
    } else {

        fp = inc_fopen_search(file, &path, omode, fmode);


        hash_add(&hi, nasm_strdup(file), path);


        if (path || omode != INC_NEEDED)
            strlist_add(dhead, file);
    }

    if (path && !fp && omode != INC_PROBE)
        fp = nasm_open_read(path, fmode);

    if (omode == INC_NEEDED && !fp) {
        if (!path)
            errno = ENOENT;

        nasm_nonfatal("unable to open include file `%s': %s",
                      file, strerror(errno));
    }

    if (found_path)
        *found_path = path;

    return fp;
}
