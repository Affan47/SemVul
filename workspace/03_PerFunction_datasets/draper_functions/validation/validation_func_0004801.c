terminate_description(autoindex_config_rec *d, char *desc,
                                   apr_int32_t autoindex_opts, int desc_width)
{
    int maxsize = desc_width;
    register int x;


    if (d->desc_adjust == K_UNSET) {
        if (autoindex_opts & SUPPRESS_ICON) {
            maxsize += 6;
        }
        if (autoindex_opts & SUPPRESS_LAST_MOD) {
            maxsize += 19;
        }
        if (autoindex_opts & SUPPRESS_SIZE) {
            maxsize += 7;
        }
    }
    for (x = 0; desc[x] && ((maxsize > 0) || (desc[x] == '<')); x++) {
        if (desc[x] == '<') {
            while (desc[x] != '>') {
                if (!desc[x]) {
                    maxsize = 0;
                    break;
                }
                ++x;
            }
        }
        else if (desc[x] == '&') {

            --maxsize;
            for ( ; desc[x] != ';'; ++x) {
                if (desc[x] == '\0') {
                     maxsize = 0;
                     break;
                }
            }
        }
        else {
            --maxsize;
        }
    }
    if (!maxsize && desc[x] != '\0') {
        desc[x - 1] = '>';
        desc[x] = '\0';
    }
    return desc;
}
