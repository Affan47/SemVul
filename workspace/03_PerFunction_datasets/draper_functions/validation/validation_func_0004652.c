extract_messageid(const char *overview)
{
    const char *p, *end;
    int count;

    for (p = overview, count = 0; count < 4; count++) {
        p = strchr(p + 1, '\t');
        if (p == NULL)
            return NULL;
    }
    p++;
    end = strchr(p, '\t');
    if (end == NULL)
        return NULL;
    return xstrndup(p, end - p);
}
