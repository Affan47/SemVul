process_client_headers (struct conn_s *connptr, orderedmap hashofheaders)
{
        static const char *skipheaders[] = {
                "host",
                "keep-alive",
                "proxy-connection",
                "te",
                "trailers",
                "upgrade"
        };
        int i;
        size_t iter;
        int ret = 0;

        char *data, *header;


        if (connptr->server_fd == -1 || connptr->show_stats
            || (connptr->connect_method && ! UPSTREAM_IS_HTTP(connptr))) {
                log_message (LOG_INFO,
                             "Not sending client headers to remote machine");
                return 0;
        }


        connptr->content_length.client = get_content_length (hashofheaders);


        if (connptr->content_length.client == -1 && is_chunked_transfer (hashofheaders))
                connptr->content_length.client = -2;


        remove_connection_headers (hashofheaders);


        for (i = 0; i != (sizeof (skipheaders) / sizeof (char *)); i++) {
                orderedmap_remove (hashofheaders, skipheaders[i]);
        }


        ret = write_via_header (connptr->server_fd, hashofheaders,
                                connptr->protocol.major,
                                connptr->protocol.minor);
        if (ret < 0) {
                indicate_http_error (connptr, 503,
                                     "Could not send data to remote server",
                                     "detail",
                                     "A network error occurred while "
                                     "trying to write data to the remote web server.",
                                     NULL);
                goto PULL_CLIENT_DATA;
        }


        iter = 0;
        while((iter = orderedmap_next(hashofheaders, iter, &data, &header))) {
                if (!is_anonymous_enabled (config)
                    || anonymous_search (config, data) > 0) {
                        ret =
                            write_message (connptr->server_fd,
                                           "%s: %s\r\n", data, header);
                        if (ret < 0) {
                                indicate_http_error (connptr, 503,
                                                     "Could not send data to remote server",
                                                     "detail",
                                                     "A network error occurred while "
                                                     "trying to write data to the "
                                                     "remote web server.",
                                                     NULL);
                                goto PULL_CLIENT_DATA;
                        }
                }
        }
#if defined(XTINYPROXY_ENABLE)
        if (config->add_xtinyproxy)
                add_xtinyproxy_header (connptr);
#endif


        if (safe_write (connptr->server_fd, "\r\n", 2) < 0)
                return -1;


PULL_CLIENT_DATA:
        if (connptr->content_length.client > 0) {
                ret = pull_client_data (connptr,
                                        connptr->content_length.client, 1);
        } else if (connptr->content_length.client == -2)
                ret = pull_client_data_chunked (connptr);

        return ret;
}
