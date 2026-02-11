ReadBytes(int in_fd) {
    uint8_t recv_bytes[1024];
    int ret;

    if ((ret = read(in_fd, recv_bytes, 1024)) < 0) {
		if (errno == EINTR || errno == EAGAIN)
			return 0;

        snprintf(errstr, STATUS_MAX, "TCP server client read() error for %s: %s",
                 GetRemoteAddr(in_fd).c_str(), strerror(errno));
        globalreg->messagebus->InjectMessage(errstr, MSGFLAG_ERROR);
        return -1;
    }

    if (ret <= 0) {
        snprintf(errstr, STATUS_MAX, "TCP server client read() ended for %s",
				 GetRemoteAddr(in_fd).c_str());
        globalreg->messagebus->InjectMessage(errstr, MSGFLAG_ERROR);
        return -1;
    }

    if (read_buf_map[in_fd]->InsertData(recv_bytes, ret) == 0) {
        snprintf(errstr, STATUS_MAX, "TCP server client %s read error, ring "
				 "buffer full", GetRemoteAddr(in_fd).c_str());
        globalreg->messagebus->InjectMessage(errstr, MSGFLAG_ERROR);
        return -1;
    }

    return ret;
}
