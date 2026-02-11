vtag_new(const char *vendor_string, int *error)
    {
    struct vtag *s;
    int error_;

    if (!error)
        error = &error_;

    if (!(s = vtag_create(error)))
        return NULL;

    if (!(s->vendor_string = strdup(vendor_string)))
        {
        vtag_cleanup(s);
        *error = VE_ALLOCATION;
        return NULL;
        }

    return s;
    }
