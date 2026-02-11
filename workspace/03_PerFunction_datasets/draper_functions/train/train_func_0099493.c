virt_ftruncate(int fd, off_t length)
{
    int res;
    int errno_save = errno;

    res = av_fd_truncate(fd, length);
    if(res < 0) {
        errno = -res;
        return -1;
    }

    errno = errno_save;
    return 0;
}
