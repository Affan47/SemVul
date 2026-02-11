init(void)
{
    OBJ_CONSTRUCT(&tables, opal_pointer_array_t);
    opal_pointer_array_init(&tables, 1, INT_MAX, 1);

    if (0 == strcmp(mca_db_print_component.filename, "-")) {
        fpout = stdout;
    } else if (0 == strcmp(mca_db_print_component.filename, "+")) {
        fpout = stderr;
    } else if (NULL == (fpout = fopen(mca_db_print_component.filename, "w"))) {
        opal_output(0, "ERROR: cannot open log file %s", mca_db_print_component.filename);
        return OPAL_ERROR;
    }

    return OPAL_SUCCESS;
}
