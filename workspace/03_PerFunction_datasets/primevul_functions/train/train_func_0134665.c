int bus_socket_connect(sd_bus *b) {
        bool inotify_done = false;
        int r;

        assert(b);

        for (;;) {
                assert(b->input_fd < 0);
                assert(b->output_fd < 0);
                assert(b->sockaddr.sa.sa_family != AF_UNSPEC);

                b->input_fd = socket(b->sockaddr.sa.sa_family, SOCK_STREAM|SOCK_CLOEXEC|SOCK_NONBLOCK, 0);
                if (b->input_fd < 0)
                        return -errno;

                b->input_fd = fd_move_above_stdio(b->input_fd);

                b->output_fd = b->input_fd;
                bus_socket_setup(b);

                if (connect(b->input_fd, &b->sockaddr.sa, b->sockaddr_size) < 0) {
                        if (errno == EINPROGRESS) {


                                bus_close_inotify_fd(b);


                                bus_set_state(b, BUS_OPENING);
                                return 1;
                        }

                        if (IN_SET(errno, ENOENT, ECONNREFUSED) &&
                            b->watch_bind &&
                            b->sockaddr.sa.sa_family == AF_UNIX &&
                            b->sockaddr.un.sun_path[0] != 0) {


                                bus_close_io_fds(b);

                                if (inotify_done) {


                                        bus_set_state(b, BUS_WATCH_BIND);
                                        return 1;
                                }


                                r = bus_socket_inotify_setup(b);
                                if (r < 0)
                                        return r;


                                inotify_done = true;

                        } else
                                return -errno;
                } else
                        break;
        }


        bus_close_inotify_fd(b);

        return bus_socket_start_auth(b);
}
