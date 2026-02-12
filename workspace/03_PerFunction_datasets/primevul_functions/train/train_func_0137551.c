int main(int argc, char** argv)
{
    GIOChannel* ch;
    int server_fd;
    struct sockaddr_un addr;
#ifndef DISABLE_DAEMONIZE
    int fd, pid;

    long open_max;
    long i;
#endif

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    if (argc < 2)

        get_socket_name( addr.sun_path, sizeof( addr.sun_path ) );
    else if (strlen(argv[1]) >= sizeof(addr.sun_path))

        return 1;
    else

        strncpy(addr.sun_path, argv[1], sizeof(addr.sun_path) - 1);

    socket_file = addr.sun_path;

    server_fd = create_socket(&addr);

    if( server_fd < 0 )
        return 1;

#ifndef DISABLE_DAEMONIZE

    if ((pid = fork()) < 0) {
        g_error("can't fork");
    }
    else if (pid != 0) {

        exit(0);
    }


    setsid();


    if (chdir("/") < 0) {
        g_error("can't change directory to /");
    }

    open_max = sysconf (_SC_OPEN_MAX);
    for (i = 0; i < open_max; i++)
    {

        if (i != server_fd)
            fcntl (i, F_SETFD, FD_CLOEXEC);
    }


    fd = open ("/dev/null", O_RDONLY);
    if (fd != -1)
    {
        dup2 (fd, 0);
        close (fd);
    }
    fd = open ("/dev/null", O_WRONLY);
    if (fd != -1)
    {
        dup2 (fd, 1);
        dup2 (fd, 2);
        close (fd);
    }
#endif

    signal(SIGHUP, terminate);
    signal(SIGINT, terminate);
    signal(SIGQUIT, terminate);
    signal(SIGTERM, terminate);
    signal(SIGPIPE, SIG_IGN);

    ch = g_io_channel_unix_new(server_fd);
    if(!ch)
        return 1;
    g_io_add_watch(ch, G_IO_IN|G_IO_PRI, on_new_conn_incoming, NULL);
    g_io_add_watch(ch, G_IO_ERR, on_server_conn_close, NULL);
    g_io_channel_unref(ch);

#if !GLIB_CHECK_VERSION(2, 36, 0)
    g_type_init();
#endif

    hash = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);

    main_loop = g_main_loop_new( NULL, TRUE );
    g_main_loop_run( main_loop );
    g_main_loop_unref( main_loop );

    unlink(addr.sun_path);

    g_hash_table_destroy(hash);
    return 0;
}
