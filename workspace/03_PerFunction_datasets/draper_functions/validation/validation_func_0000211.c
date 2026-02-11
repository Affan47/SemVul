_parse_uri(const char *uri, bool *protocol, char *hostname,
                       size_t namesize, int *port) {

    if (!strncasecmp(uri, "http://", CONST_STRLEN("http://"))) {
        *protocol = false;
        *port = 80;
    } else if (!strncasecmp(uri, "https://", CONST_STRLEN("https://"))) {
        *protocol = true;
        *port = 443;
    } else {
        return false;
    }

    char *t1 = strstr(uri, "://");
    t1 += 3;
    char *t2 = strstr(t1, "/");
    if (t2 == NULL)
        t2 = (char *) uri + strlen(uri);

    if (t2 - t1 + 1 > namesize)
        return false;
    qstrncpy(hostname, namesize, t1, t2 - t1);

    t1 = strstr(hostname, ":");
    if (t1 != NULL) {
        *t1 = '\0';
        *port = atoi(t1 + 1);
    }

    return true;
}
