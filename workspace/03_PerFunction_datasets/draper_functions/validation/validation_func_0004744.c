db2index_add_indexed_attr(backend *be, char *attrString)
{
    char *iptr = NULL;
    char *mptr = NULL;
    Slapi_Entry *e;
    struct berval *vals[2];
    struct berval val;
    char *ptr;
    char *next;

    vals[0] = &val;
    vals[1] = NULL;

    if (NULL == (iptr = strchr(attrString, ':'))) {
        return(0);
    }
    e = slapi_entry_alloc();
    iptr[0] = '\0';
    iptr++;


    val.bv_val = attrString+1;
    val.bv_len = strlen(attrString);

    slapi_entry_add_values(e,"cn",vals);

    if (NULL != (mptr = strchr(iptr, ':'))) {
        mptr[0] = '\0';
        mptr++;
    }


    for (ptr = strtok_r(iptr, ", ", &next);
         ptr;
         ptr = strtok_r(NULL, ", ", &next)) {
        val.bv_val = ptr;
        val.bv_len = strlen(ptr);

        slapi_entry_add_values(e,"nsIndexType",vals);
    }

    if (NULL != mptr) {
        for (ptr = strtok_r(mptr, ", ", &next);
             ptr;
             ptr = strtok_r(NULL, ", ", &next)) {
            val.bv_val = ptr;
            val.bv_len = strlen(ptr);

            slapi_entry_add_values(e,"nsMatchingRule",vals);
        }
    }

    attr_index_config(be, "from db2index()", 0, e, 0, 0);
    slapi_entry_free(e);

    return(0);
}
