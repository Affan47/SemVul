spawnvp(const char *prog, char **args) {
    int fds[2], rc;

    if (pipe(fds) == -1)
        return -1;

    if ((rc = fork()) == -1) {
        return -1;
    } else if (rc == 0) {
        close(fds[0]);
        dup2(fds[1], 1);
        int devnull = open("/dev/null", O_RDONLY);
        if (devnull != -1) {
            dup2(devnull, 0);
            close(devnull);
        }
        execvp(prog, args);
        _exit(99);
    } else {
        close(fds[1]);
        fFd = fds[0];
    }
    return 0;
}
