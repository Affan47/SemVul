fd_seek2(int fd1, int fd2, ft_off offset, const char * path1, const char * path2)
{
    int err = fd_seek(fd1, offset, path1);
    if (err == 0)
        err = fd_seek(fd2, offset, path2);
    return err;
}
