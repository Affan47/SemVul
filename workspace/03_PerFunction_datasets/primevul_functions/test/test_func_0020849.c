static int annotate_canon_value(struct buf *value, int type)
{
    char *p = NULL;
    unsigned long uwhatever = 0;
    long whatever = 0;


    if (value->s == NULL)
        return 0;

    switch (type) {
    case ATTRIB_TYPE_STRING:

        break;

    case ATTRIB_TYPE_BOOLEAN:

        if (value->len == 4 && !strncasecmp(value->s, "true", 4)) {
            buf_reset(value);
            buf_appendcstr(value, "true");
            buf_cstring(value);
        }
        else if (value->len == 5 && !strncasecmp(value->s, "false", 5)) {
            buf_reset(value);
            buf_appendcstr(value, "false");
            buf_cstring(value);
        }
        else return IMAP_ANNOTATION_BADVALUE;
        break;

    case ATTRIB_TYPE_UINT:

        errno = 0;
        buf_cstring(value);
        uwhatever = strtoul(value->s, &p, 10);
        if ((p == value->s)
            || (*p != '\0')
            || (unsigned)(p - value->s) != value->len

            || errno
            || strchr(value->s, '-')) {
            return IMAP_ANNOTATION_BADVALUE;
        }
        break;

    case ATTRIB_TYPE_INT:

        errno = 0;
        buf_cstring(value);
        whatever = strtol(value->s, &p, 10);
        if ((p == value->s)
            || (*p != '\0')
            || (unsigned)(p - value->s) != value->len

            || errno) {
            return IMAP_ANNOTATION_BADVALUE;
        }
        break;

    default:

        return IMAP_ANNOTATION_BADVALUE;
    }

    if (whatever || uwhatever)
        return 0;

    return 0;
}
