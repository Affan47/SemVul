cpl_column_copy_data_string(cpl_column *column,
                                           const char **data)
{

    const char *fid    = "cpl_column_copy_data_string";
    cpl_type     type   = cpl_column_get_type(column);
    cpl_size     length = cpl_column_get_size(column);


    if (data == 0x0 || column == 0x0)
        return cpl_error_set(fid, CPL_ERROR_NULL_INPUT);

    if (type != CPL_TYPE_STRING)
        return cpl_error_set(fid, CPL_ERROR_TYPE_MISMATCH);


    while (length--) {
        if (column->values->s[length])
            cpl_free(column->values->s[length]);
        if (data[length])
            column->values->s[length] = cpl_strdup(data[length]);
        else
            column->values->s[length] = NULL;
    }

    return CPL_ERROR_NONE;

}
