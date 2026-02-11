indx_parse(const char *file_name)
{
    INDX_ROOT *indx = _indx_parse(file_name);


    if (!indx) {
        size_t len   = strlen(file_name);
        char *backup = malloc(len + 8);

        strcpy(backup, file_name);
        strcpy(backup + len - 10, "BACKUP/index.bdmv");

        indx = _indx_parse(backup);

        X_FREE(backup);
    }

    return indx;
}
