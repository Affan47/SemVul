received_message(GIOChannel *channel, GIOCondition condition, gpointer data) {
    gint source = g_io_channel_unix_get_fd(channel);
    gint csock, rval;
    gchar *buf;


    buf = g_malloc(PATH_MAX);
    while ((csock = accept(source, 0, 0)) != -1) {
        do {
            bzero(buf, PATH_MAX);
            if ((rval = read(csock, buf, PATH_MAX)) < 0) {
                fprintf(stderr, "server: read error: %s", strerror(errno));
                continue;
            }
            else if (rval == 0) {

            }
            else {
                if (strncmp(buf, SOCKET_TEST, strlen(SOCKET_TEST)) == 0) {
                    continue;
                }
                if (strncmp(buf, SOCKET_PLYC, strlen(SOCKET_PLYC)) == 0) {
                    gchar *file = buf + strlen(SOCKET_PLYC);
                    if (gp_increase_playcount(NULL, file, 1) == FALSE) {

                        register_playcount(file);
                    }
                }
            }
        }
        while (rval > 0);
        close(csock);
    }
    g_free(buf);

    return TRUE;
}
