int am_check_url(request_rec *r, const char *url)
{
    const char *i;

    if (url == NULL) {
        return HTTP_BAD_REQUEST;
    }

    for (i = url; *i; i++) {
        if (*i >= 0 && *i < ' ') {

            AM_LOG_RERROR(APLOG_MARK, APLOG_ERR, HTTP_BAD_REQUEST, r,
                          "Control character detected in URL.");
            return HTTP_BAD_REQUEST;
        }
        if (*i == '\\') {


            AM_LOG_RERROR(APLOG_MARK, APLOG_ERR, HTTP_BAD_REQUEST, r,
                          "Backslash character detected in URL.");
            return HTTP_BAD_REQUEST;
        }
    }

    if (strstr(url, "///") == url) {
        AM_LOG_RERROR(APLOG_MARK, APLOG_ERR, HTTP_BAD_REQUEST, r,
                          "URL starts with '///'");
        return HTTP_BAD_REQUEST;
    }

    return OK;
}
