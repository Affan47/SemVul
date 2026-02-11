do_unrar(ventry *ve, struct archfile *fil)
{
    int res;
    struct rarfile *rfil;
    char *tmpfile;
    int fd;

    res = av_get_tmpfile(&tmpfile);
    if(res < 0)
        return res;

    fd = open(tmpfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if(fd == -1) {
        res = -errno;
        av_log(AVLOG_ERROR, "RAR: Could not open %s: %s", tmpfile,
               strerror(errno));
        av_del_tmpfile(tmpfile);
        return res;
    }

    res = get_rar_file(ve, fil, fd);
    if(res < 0) {
        close(fd);
        av_del_tmpfile(tmpfile);
        return res;
    }

    AV_NEW(rfil);
    rfil->tmpfile = tmpfile;
    rfil->fd = fd;

    fil->data = rfil;

    return 0;
}
