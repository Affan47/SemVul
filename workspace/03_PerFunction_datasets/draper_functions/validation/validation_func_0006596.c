extract_next_option(char *str, char **pagerange, char **key, char **value)
{
    char *p = str;
    char quotechar;

    *pagerange = NULL;
    *key = NULL;
    *value = NULL;

    if (!str)
        return NULL;


    while (*p && (isspace(*p) || *p == ',')) p++;

    if (!*p)
        return NULL;


    if (prefixcmp(p, "even:") == 0 || prefixcmp(p, "odd:") == 0 || isdigit(*p)) {
        *pagerange = p;
        p = strchr(p, ':');
        if (!p)
            return NULL;
        *p = '\0';
        p++;
    }


    if (*p == '\'' || *p == '\"') {
        quotechar = *p;
        *key = p +1;
        p = strchr(*key, quotechar);
        if (!p)
            return NULL;
    }
    else {
        *key = p;
        while (*p && *p != ':' && *p != '=' && *p != ' ') p++;
    }

    if (*p != ':' && *p != '=') {
        if (!*p)
            return NULL;
        else if (isspace(*p)) {
            *p = '\0';
            return p +1;
        }
        return p;
    }

    *p++ = '\0';

    if (*p == '\"' || *p == '\'') {
        quotechar = *p;
        *value = p +1;
        p = strchr(*value, quotechar);
        if (!p)
            return NULL;
        *p = '\0';
        p++;
    }
    else {
        *value = p;
        while (*p && *p != ' ' && *p != ',') p++;
        if (*p == '\0')
            return NULL;
        *p = '\0';
        p++;
    }

    return *p ? p : NULL;
}
