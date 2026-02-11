open_wrapper (const char *func, const char *pathname, int flags, mode_t mode)
{
    int (*_open) (const char *pathname, int flags, mode_t mode);
    gchar *new_path = NULL;
    int fd;

    _open = (int (*)(const char *pathname, int flags, mode_t mode)) dlsym (RTLD_NEXT, func);

    if (strcmp (pathname, "/dev/console") == 0)
    {
        if (console_fd < 0)
        {
            console_fd = _open ("/dev/null", flags, mode);
            fcntl (console_fd, F_SETFD, FD_CLOEXEC);
        }
        return console_fd;
    }

    new_path = redirect_path (pathname);
    fd = _open (new_path, flags, mode);
    g_free (new_path);

    return fd;
}
