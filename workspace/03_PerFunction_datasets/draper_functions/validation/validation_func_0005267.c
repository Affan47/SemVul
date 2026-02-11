accept_connection (u_short port)
{
    static int sock = -1;
    int connection;
    struct sockaddr_in name;
    struct sockaddr client;
    int socklen;
    fd_set ifds;
    int nfds;
    int sockopt;


    debug("Creating source port to forward.\n");
    sock = socket (PF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        fatal("socket() failed, errno=%d\n", socket_errno());
    sockopt = 1;
    setsockopt (sock, SOL_SOCKET, SO_REUSEADDR,
                (void*)&sockopt, sizeof(sockopt));


    name.sin_family = AF_INET;
    name.sin_port = htons (port);
    name.sin_addr.s_addr = htonl (INADDR_ANY);
    if (bind (sock, (struct sockaddr *) &name, sizeof (name)) < 0)
        fatal ("bind() failed, errno=%d\n", socket_errno());

    if (listen( sock, 1) < 0)
        fatal ("listen() failed, errno=%d\n", socket_errno());


    debug ("waiting new connection at port %d (socket=%d)\n", port, sock);
    nfds = sock + 1;
    do {
        int n;
        struct timeval *ptmo = NULL;
#ifdef _WIN32
        struct timeval tmo;
        tmo.tv_sec = 0;
        tmo.tv_usec = 100*1000;
        ptmo = &tmo;
#endif
        FD_ZERO (&ifds);
        FD_SET ((SOCKET)sock, &ifds);
#ifndef _WIN32
        FD_SET (0, &ifds);
#endif
        n = select (nfds, &ifds, NULL, NULL, ptmo);
        if (n == -1) {
            fatal ("select() failed, %d\n", socket_errno());
            exit (1);
        }
#ifdef _WIN32
        if (0 < stdindatalen()) {
            FD_SET (0, &ifds);
            n++;
        }
#endif
        if (0 < n) {
            if (FD_ISSET(0, &ifds) && (getchar() <= 0)) {

                debug ("Give-up waiting port because stdin is closed.");
                exit(0);
            }
            if (FD_ISSET(sock, &ifds))
                break;
        }
    } while (1);
    socklen = sizeof(client);
    connection = accept( sock, &client, &socklen);
    if ( connection < 0 )
        fatal ("accept() failed, errno=%d\n", socket_errno());
    return connection;
}
