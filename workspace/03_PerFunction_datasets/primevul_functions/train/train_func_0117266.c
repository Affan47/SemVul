static int wsgi_parse_option(apr_pool_t *p, const char **line,
                             const char **name, const char **value)
{
    const char *str = *line, *strend;

    while (*str && apr_isspace(*str))
        ++str;

    if (!*str || *str == '=') {
        *line = str;
        return !APR_SUCCESS;
    }


    strend = str;
    while (*strend && *strend != '=' && !apr_isspace(*strend))
        ++strend;

    if (*strend != '=') {
        *line = str;
        return !APR_SUCCESS;
    }

    *name = apr_pstrndup(p, str, strend-str);

    *line = strend+1;


    *value = ap_getword_conf(p, line);

    return APR_SUCCESS;
}
