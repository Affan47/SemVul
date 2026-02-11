register_readfd(int fd, void (*func) (int, void *), void *data)
{
    if (external_readfdlen < NUM_EXTERNAL_FDS) {
        external_readfd[external_readfdlen] = fd;
        external_readfdfunc[external_readfdlen] = func;
        external_readfd_data[external_readfdlen] = data;
        external_readfdlen++;
        DEBUGMSGTL(("fd_event_manager:register_readfd", "registered fd %d\n", fd));
        return FD_REGISTERED_OK;
    } else {
        snmp_log(LOG_CRIT, "register_readfd: too many file descriptors\n");
        return FD_REGISTRATION_FAILED;
    }
}
