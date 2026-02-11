at2_read_buffer(PrivAT2data *privdata, double timeout)
{
    char buf[MAX_READ + 1];
    int ret;
    size_t count;
    signed int s;
    fd_set read_fd;
    struct timeval tv;

    if (privdata->fd == -1) {
        error(errno, "AT2[%s]: at2_read_buffer: fd = -1. Can not read",
              octstr_get_cstr(privdata->name));
        return;
    }
    count = MAX_READ;

#ifdef SSIZE_MAX
    if (count > SSIZE_MAX)
        count = SSIZE_MAX;
#endif

    if (timeout <= 0) {
        tv.tv_sec = 0;
        tv.tv_usec = 1000;
    } else {
      int usecs = timeout * 1000000;
      tv.tv_sec = usecs / 1000000;
      tv.tv_usec = usecs % 1000000;
    }

    FD_ZERO(&read_fd);
    FD_SET(privdata->fd, &read_fd);
    ret = select(privdata->fd + 1, &read_fd, NULL, NULL, &tv);
    if (ret == -1) {
        if (!(errno == EINTR || errno == EAGAIN))
            error(errno, "AT2[%s]: error on select", octstr_get_cstr(privdata->name));
        return;
    }

    if (ret == 0)
        return;

    s = read(privdata->fd, buf, count);
    if (s < 0) {
        error(errno, "AT2[%s]: at2_read_buffer: Error during read",
              octstr_get_cstr(privdata->name));
        at2_close_device(privdata);
    } else {
        octstr_append_data(privdata->ilb, buf, s);
        if(privdata->use_telnet)
            at2_scan_for_telnet_escapes(privdata);
    }
}
