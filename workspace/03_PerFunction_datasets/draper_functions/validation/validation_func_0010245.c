irmo_sockbase_open(IrmoNetSocketClass *socket_class,
                                   int family)
{
        SockBaseSocket *result;
        int sock;
        int opts;


        sock = socket(family, SOCK_DGRAM, 0);

        if (sock < 0) {
                return NULL;
        }


#ifdef _WIN32

        {
                int trueval=1;
                ioctlsocket(sock, FIONBIO, &trueval);
        }
#else


        opts = fcntl(sock, F_GETFL);

        if (opts < 0) {
                irmo_error_report("irmo_sockbase_block"
                                  "cannot make socket nonblocking (%s)",
                                  strerror(errno));
                closesocket(sock);
                return NULL;
        }

        opts |= O_NONBLOCK;

        if (fcntl(sock, F_SETFL, opts) < 0) {
                irmo_error_report("irmo_sockbase_block"
                                  "cannot make socket nonblocking (%s)",
                                  strerror(errno));
                closesocket(sock);
                return NULL;
        }
#endif


        result = irmo_new0(SockBaseSocket, 1);
        result->irmo_socket.socket_class = socket_class;
        result->sock = sock;
        result->recvbuf = irmo_malloc0(RECV_BUFFER_SIZE);

        return result;
}
