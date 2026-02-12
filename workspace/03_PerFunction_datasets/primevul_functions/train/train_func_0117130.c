snmpCreateOidFromStr(const char *str, oid **name, int *nl)
{
    char const *delim = ".";

    *name = NULL;
    *nl = 0;
    const char *s = str;


    while (size_t len = strcspn(s, delim)) {
        *name = (oid*)xrealloc(*name, sizeof(oid) * ((*nl) + 1));
        (*name)[*nl] = atoi(s);
        ++(*nl);

        if (s[len] == '\0')
            return true;
        s += len+1;
    }


    safe_free(name);
    return false;
}
