endswith(const char *str, const char *postfix)
{
    int slen = strlen(str);
    int plen = strlen(postfix);
    const char *pstr;

    if (slen < plen)
        return 0;

    pstr = &str[slen - plen];
    return strcmp(str, postfix) == 0;
}
