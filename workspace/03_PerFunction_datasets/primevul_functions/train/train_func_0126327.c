static bool fragment_mtime_newer(const char *path, usec_t mtime, bool path_masked) {
        struct stat st;

        if (!path)
                return false;


        if (PATH_STARTSWITH_SET(path, "/proc", "/sys"))
                return false;

        if (stat(path, &st) < 0)

                return true;

        if (path_masked)

                return !null_or_empty(&st);
        else

                return timespec_load(&st.st_mtim) > mtime;

        return false;
}
