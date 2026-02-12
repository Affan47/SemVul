EXPORTED xmlURIPtr parse_uri(unsigned meth, const char *uri, unsigned path_reqd,
                    const char **errstr)
{
    xmlURIPtr p_uri;


    if ((p_uri = xmlParseURI(uri)) == NULL) {
        *errstr = "Illegal request target URI";
        goto bad_request;
    }

    if (p_uri->scheme) {


        if (strcasecmp(p_uri->scheme, "http") &&
            strcasecmp(p_uri->scheme, "https")) {
            *errstr = "Unsupported URI scheme";
            goto bad_request;
        }
    }


    if (path_reqd && (!p_uri->path || !*p_uri->path)) {
        *errstr = "Empty path in target URI";
        goto bad_request;
    }
    else if (p_uri->path) {
        size_t pathlen = strlen(p_uri->path);
        if ((p_uri->path[0] != '/') &&
            (strcmp(p_uri->path, "*") || (meth != METH_OPTIONS))) {

            *errstr = "Illegal request target URI";
            goto bad_request;
        }
        else if (strstr(p_uri->path, "/../")) {

            *errstr = "Illegal request target URI";
            goto bad_request;
        }
        else if (pathlen >= 3 && !strcmp("/..", p_uri->path + pathlen - 3)) {

            *errstr = "Illegal request target URI";
            goto bad_request;
        }
        else if (pathlen > MAX_MAILBOX_PATH) {
            *errstr = "Request target URI too long";
            goto bad_request;
        }
    }

    return p_uri;

  bad_request:
    if (p_uri) xmlFreeURI(p_uri);
    return NULL;
}
