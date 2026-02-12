static char *sftp_parse_longname(const char *longname,
        enum sftp_longname_field_e longname_field) {
    const char *p, *q;
    size_t len, field = 0;
    char *x;

    p = longname;

    while(field != longname_field) {
        if(isspace(*p)) {
            field++;
            p++;
            while(*p && isspace(*p)) {
                p++;
            }
        } else {
            p++;
        }
    }

    q = p;
    while (! isspace(*q)) {
        q++;
    }


    len = q - p + 1;
    x = malloc(len);
    if (x == NULL) {
      return NULL;
    }

    snprintf(x, len, "%s", p);

    return x;
}
