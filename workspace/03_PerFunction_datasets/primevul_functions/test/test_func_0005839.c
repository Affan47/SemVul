static int get_all_headers (int fd, orderedmap hashofheaders)
{
        char *line = NULL;
        char *header = NULL;
        int count;
        char *tmp;
        ssize_t linelen;
        ssize_t len = 0;
        unsigned int double_cgi = FALSE;

        assert (fd >= 0);
        assert (hashofheaders != NULL);

        for (count = 0; count < MAX_HEADERS; count++) {
                if ((linelen = readline (fd, &line)) <= 0) {
                        safefree (header);
                        safefree (line);
                        return -1;
                }


                if (CHECK_CRLF (line, linelen) || !CHECK_LWS (line, linelen)) {
                        if (!double_cgi
                            && len > 0
                            && add_header_to_connection (hashofheaders, header,
                                                         len) < 0) {
                                safefree (header);
                                safefree (line);
                                return -1;
                        }

                        len = 0;
                }


                if (CHECK_CRLF (line, linelen)) {
                        safefree (header);
                        safefree (line);
                        return 0;
                }


                if (linelen >= 5 && strncasecmp (line, "HTTP/", 5) == 0) {
                        double_cgi = TRUE;
                }


                tmp = (char *) saferealloc (header, len + linelen);
                if (tmp == NULL) {
                        safefree (header);
                        safefree (line);
                        return -1;
                }

                header = tmp;
                memcpy (header + len, line, linelen);
                len += linelen;

                safefree (line);
        }


        safefree (header);
        safefree (line);
        return -1;
}
