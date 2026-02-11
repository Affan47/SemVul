handle_send_link(int s, char *path, char *buffer)
{
    syncmsg msg;
    unsigned int len;
    int ret;

    if(readx(s, &msg.data, sizeof(msg.data)))
        return -1;

    if(msg.data.id != ID_DATA) {
        fail_message(s, "invalid data message: expected ID_DATA");
        return -1;
    }

    len = ltohl(msg.data.size);
    if(len > SYNC_DATA_MAX) {
        fail_message(s, "oversize data message");
        return -1;
    }
    if(readx(s, buffer, len))
        return -1;

    ret = symlink(buffer, path);
    if(ret && errno == ENOENT) {
        mkdirs(path);
        ret = symlink(buffer, path);
    }
    if(ret) {
        fail_errno(s);
        return -1;
    }

    if(readx(s, &msg.data, sizeof(msg.data)))
        return -1;

    if(msg.data.id == ID_DONE) {
        msg.status.id = ID_OKAY;
        msg.status.msglen = 0;
        if(writex(s, &msg.status, sizeof(msg.status)))
            return -1;
    } else {
        fail_message(s, "invalid data message: expected ID_DONE");
        return -1;
    }

    return 0;
}
