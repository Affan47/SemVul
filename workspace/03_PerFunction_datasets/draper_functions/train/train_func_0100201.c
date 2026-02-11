closeMostFDs(const set<int> & exceptions)
{
    int maxFD = 0;
    maxFD = sysconf(_SC_OPEN_MAX);
    for (int fd = 0; fd < maxFD; ++fd)
        if (fd != STDIN_FILENO && fd != STDOUT_FILENO && fd != STDERR_FILENO
            && exceptions.find(fd) == exceptions.end())
            close(fd);
}
