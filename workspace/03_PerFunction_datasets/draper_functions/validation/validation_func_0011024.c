virt_close(int fd)
{
    int res;
    int errno_save = errno;

    res = av_fd_close(fd);
    if(res < 0) {
        errno = -res;
        return -1;
    }

    errno = errno_save;
    return 0;
}
