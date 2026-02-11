file_exists(const char *filename, const char *ext)
{
    char *final;
    struct stat buf;
    int ret;

    if (NULL != ext) {
        asprintf(&final, "%s.%s", filename, ext);
    } else {
        final = strdup(filename);
    }
    if (NULL == final) {
        return 0;
    }
    ret = stat(final, &buf);
    free(final);
    return (0 == ret ? 1 : 0);
}
