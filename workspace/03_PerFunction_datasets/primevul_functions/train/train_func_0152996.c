EXPORTED int etagcmp(const char *hdr, const char *etag)
{
    size_t len;

    if (!etag) return -1;
    if (!strcmp(hdr, "*")) return 0;

    len = strlen(etag);
    if (!strncmp(hdr, "W/", 2)) hdr+=2;
    if (*hdr++ != '\"') return 1;
    if (strlen(hdr) != len+1) return 1;
    if (hdr[len] != '\"') return 1;

    return strncmp(hdr, etag, len);
}
