SCHANadd(CHANNEL *cp, time_t wake, void *event, innd_callback_func waker,
         void *arg)
{
    if (!CHANsleeping(cp)) {
        channels.sleep_count++;
        FD_SET(cp->fd, &channels.sleep_set);
    }
    if (cp->fd > channels.max_sleep_fd)
        channels.max_sleep_fd = cp->fd;
    cp->Waketime = wake;
    cp->Waker = waker;
    if (cp->Argument != arg) {
        free(cp->Argument);
        cp->Argument = arg;
    }
    cp->Event = event;
}
