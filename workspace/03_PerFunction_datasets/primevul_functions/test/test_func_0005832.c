static int process_server_headers (struct conn_s *connptr)
{
        static const char *skipheaders[] = {
                "keep-alive",
                "proxy-authenticate",
                "proxy-authorization",
                "proxy-connection",
        };

        char *response_line;

        orderedmap hashofheaders;
        size_t iter;
        char *data, *header;
        ssize_t len;
        int i;
        int ret;

#ifdef REVERSE_SUPPORT
        struct reversepath *reverse = config->reversepath_list;
#endif


retry:
        len = readline (connptr->server_fd, &response_line);
        if (len <= 0)
                return -1;


        if (chomp (response_line, len) == len) {


                safefree (response_line);
                goto retry;
        }

        hashofheaders = orderedmap_create (HEADER_BUCKETS);
        if (!hashofheaders) {
                safefree (response_line);
                return -1;
        }


        if (get_all_headers (connptr->server_fd, hashofheaders) < 0) {
                log_message (LOG_WARNING,
                             "Could not retrieve all the headers from the remote server.");
                orderedmap_destroy (hashofheaders);
                safefree (response_line);

                indicate_http_error (connptr, 503,
                                     "Could not retrieve all the headers",
                                     "detail",
                                     PACKAGE_NAME " "
                                     "was unable to retrieve and process headers from "
                                     "the remote web server.", NULL);
                return -1;
        }


        if (connptr->protocol.major < 1) {
                orderedmap_destroy (hashofheaders);
                safefree (response_line);
                return 0;
        }


        ret = write_message (connptr->client_fd, "%s\r\n", response_line);
        safefree (response_line);
        if (ret < 0)
                goto ERROR_EXIT;


        connptr->content_length.server = get_content_length (hashofheaders);


        remove_connection_headers (hashofheaders);


        for (i = 0; i != (sizeof (skipheaders) / sizeof (char *)); i++) {
                orderedmap_remove (hashofheaders, skipheaders[i]);
        }


        ret = write_via_header (connptr->client_fd, hashofheaders,
                                connptr->protocol.major,
                                connptr->protocol.minor);
        if (ret < 0)
                goto ERROR_EXIT;

#ifdef REVERSE_SUPPORT

        if (config->reversemagic && connptr->reversepath) {
                ret = write_message (connptr->client_fd,
                                     "Set-Cookie: " REVERSE_COOKIE
                                     "=%s; path=/\r\n", connptr->reversepath);
                if (ret < 0)
                        goto ERROR_EXIT;
        }


        if (config->reversebaseurl &&
            (header = orderedmap_find (hashofheaders, "location"))) {


                while (reverse) {
                        if (strncasecmp (header,
                                         reverse->url, (len =
                                                        strlen (reverse->
                                                                url))) == 0)
                                break;
                        reverse = reverse->next;
                }

                if (reverse) {
                        ret =
                            write_message (connptr->client_fd,
                                           "Location: %s%s%s\r\n",
                                           config->reversebaseurl,
                                           (reverse->path + 1), (header + len));
                        if (ret < 0)
                                goto ERROR_EXIT;

                        log_message (LOG_INFO,
                                     "Rewriting HTTP redirect: %s -> %s%s%s",
                                     header, config->reversebaseurl,
                                     (reverse->path + 1), (header + len));
                        orderedmap_remove (hashofheaders, "location");
                }
        }
#endif


        iter = 0;
        while ((iter = orderedmap_next(hashofheaders, iter, &data, &header))) {

                ret = write_message (connptr->client_fd,
                                     "%s: %s\r\n", data, header);
                if (ret < 0)
                        goto ERROR_EXIT;
        }
        orderedmap_destroy (hashofheaders);


        if (safe_write (connptr->client_fd, "\r\n", 2) < 0)
                return -1;

        return 0;

ERROR_EXIT:
        orderedmap_destroy (hashofheaders);
        return -1;
}
