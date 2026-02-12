static int file_ram_open(const char *path,
                         const char *region_name,
                         bool readonly,
                         bool *created,
                         Error **errp)
{
    char *filename;
    char *sanitized_name;
    char *c;
    int fd = -1;

    *created = false;
    for (;;) {
        fd = open(path, readonly ? O_RDONLY : O_RDWR);
        if (fd >= 0) {

            break;
        }
        if (errno == ENOENT) {

            fd = open(path, O_RDWR | O_CREAT | O_EXCL, 0644);
            if (fd >= 0) {
                *created = true;
                break;
            }
        } else if (errno == EISDIR) {


            sanitized_name = g_strdup(region_name);
            for (c = sanitized_name; *c != '\0'; c++) {
                if (*c == '/') {
                    *c = '_';
                }
            }

            filename = g_strdup_printf("%s/qemu_back_mem.%s.XXXXXX", path,
                                       sanitized_name);
            g_free(sanitized_name);

            fd = mkstemp(filename);
            if (fd >= 0) {
                unlink(filename);
                g_free(filename);
                break;
            }
            g_free(filename);
        }
        if (errno != EEXIST && errno != EINTR) {
            error_setg_errno(errp, errno,
                             "can't open backing store %s for guest RAM",
                             path);
            return -1;
        }


    }

    return fd;
}
