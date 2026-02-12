xz_open(const char *path, int fd, const char *mode ATTRIBUTE_UNUSED)
{
    xz_statep state;


    state = xmlMalloc(sizeof(xz_state));
    if (state == NULL)
        return NULL;
    state->size = 0;
    state->want = BUFSIZ;
    state->msg = NULL;
    state->init = 0;


    state->path = xmlMalloc(strlen(path) + 1);
    if (state->path == NULL) {
        xmlFree(state);
        return NULL;
    }
    strcpy(state->path, path);


    state->fd = fd != -1 ? fd : open(path,
#ifdef O_LARGEFILE
                                     O_LARGEFILE |
#endif
#ifdef O_BINARY
                                     O_BINARY |
#endif
                                     O_RDONLY, 0666);
    if (state->fd == -1) {
        xmlFree(state->path);
        xmlFree(state);
        return NULL;
    }


    state->start = lseek(state->fd, 0, SEEK_CUR);
    if (state->start == (uint64_t) - 1)
        state->start = 0;


    xz_reset(state);


    return (xzFile) state;
}
