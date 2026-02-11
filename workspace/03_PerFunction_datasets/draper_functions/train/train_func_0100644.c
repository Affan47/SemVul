ap_cookie_write(request_rec * r, const char *name, const char *val,
                                         const char *attrs, long maxage, ...)
{

    const char *buffer;
    const char *rfc2109;
    apr_table_t *t;
    va_list vp;


    buffer = "";
    if (maxage) {
        buffer = apr_pstrcat(r->pool, "Max-Age=", apr_ltoa(r->pool, maxage), ";", NULL);
    }


    rfc2109 = apr_pstrcat(r->pool, name, "=", val, ";", buffer,
                          attrs && *attrs ? attrs : DEFAULT_ATTRS, NULL);
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00007) LOG_PREFIX
                  "user '%s' set cookie: '%s'", r->user, rfc2109);


    va_start(vp, maxage);
    while ((t = va_arg(vp, apr_table_t *))) {
        apr_table_addn(t, SET_COOKIE, rfc2109);
    }
    va_end(vp);

    return APR_SUCCESS;

}
