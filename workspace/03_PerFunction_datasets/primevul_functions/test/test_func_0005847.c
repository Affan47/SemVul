static int extract_url (const char *url, int default_port,
                        struct request_s *request)
{
        char *p;
        int port;


        p = strchr (url, '/');
        if (p != NULL) {
                int len;
                len = p - url;
                request->host = (char *) safemalloc (len + 1);
                memcpy (request->host, url, len);
                request->host[len] = '\0';
                request->path = safestrdup (p);
        } else {
                request->host = safestrdup (url);
                request->path = safestrdup ("/");
        }

        if (!request->host || !request->path)
                goto ERROR_EXIT;


        strip_username_password (request->host);


        port = strip_return_port (request->host);
        request->port = (port != 0) ? port : default_port;


        p = strrchr (request->host, ']');
        if (p && (*(request->host) == '[')) {
                memmove(request->host, request->host + 1,
                        strlen(request->host) - 2);
                *p = '\0';
                p--;
                *p = '\0';
        }

        return 0;

ERROR_EXIT:
        if (request->host)
                safefree (request->host);
        if (request->path)
                safefree (request->path);

        return -1;
}
