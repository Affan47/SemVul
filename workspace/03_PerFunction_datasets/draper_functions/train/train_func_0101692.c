vtag_parse(void *data, size_t bytes, int *error)
    {
    struct vtag *s;
    int error_;

    if (!error)
        error = &error_;

    if (!(s = vtag_create(error)))
        return NULL;

    *error = parse(s, data, bytes);
    if (*error != VE_OK)
        {
        vtag_cleanup(s);
        return NULL;
        }

    return s;
    }
