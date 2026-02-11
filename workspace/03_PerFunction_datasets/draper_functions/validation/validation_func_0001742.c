handle_send_file(int s, char *path, mode_t mode, char *buffer)
{
    syncmsg msg;
    unsigned int timestamp = 0;
    int fd;

    fd = adb_open_mode(path, O_WRONLY | O_CREAT | O_EXCL, mode);
    if(fd < 0 && errno == ENOENT) {
        mkdirs(path);
        fd = adb_open_mode(path, O_WRONLY | O_CREAT | O_EXCL, mode);
    }
    if(fd < 0 && errno == EEXIST) {
        fd = adb_open_mode(path, O_WRONLY, mode);
    }
    if(fd < 0) {
        if(fail_errno(s))
            return -1;
        fd = -1;
    }

    for(;;) {
        unsigned int len;

        if(readx(s, &msg.data, sizeof(msg.data)))
            goto fail;

        if(msg.data.id != ID_DATA) {
            if(msg.data.id == ID_DONE) {
                timestamp = ltohl(msg.data.size);
                break;
            }
            fail_message(s, "invalid data message");
            goto fail;
        }
        len = ltohl(msg.data.size);
        if(len > SYNC_DATA_MAX) {
            fail_message(s, "oversize data message");
            goto fail;
        }
        if(readx(s, buffer, len))
            goto fail;

        if(fd < 0)
            continue;
        if(writex(fd, buffer, len)) {
            int saved_errno = errno;
            adb_close(fd);
            adb_unlink(path);
            fd = -1;
            errno = saved_errno;
            if(fail_errno(s)) return -1;
        }
    }

    if(fd >= 0) {
        struct utimbuf u;
        adb_close(fd);
        u.actime = timestamp;
        u.modtime = timestamp;
        utime(path, &u);

        msg.status.id = ID_OKAY;
        msg.status.msglen = 0;
        if(writex(s, &msg.status, sizeof(msg.status)))
            return -1;
    }
    return 0;

fail:
    if(fd >= 0)
        adb_close(fd);
    adb_unlink(path);
    return -1;
}
