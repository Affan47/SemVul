daemon_signal_done(void) {
    int saved_errno = errno;

    if (_signal_pipe[0] != -1)
        close(_signal_pipe[0]);

    if (_signal_pipe[1] != -1)
        close(_signal_pipe[1]);

    _signal_pipe[0] = _signal_pipe[1] = -1;

    errno = saved_errno;
}
