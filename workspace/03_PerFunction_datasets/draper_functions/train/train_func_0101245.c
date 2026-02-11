orte_write_hnp_contact_file(char *filename)
{
    FILE *fp;
    char *my_uri;

    fp = fopen(filename, "w");
    if (NULL == fp) {
        opal_output( 0, "Impossible to open the file %s in write mode\n",
                     filename );
        ORTE_ERROR_LOG(ORTE_ERR_FILE_OPEN_FAILURE);
        return ORTE_ERR_FILE_OPEN_FAILURE;
    }

    my_uri = orte_rml.get_contact_info();
    if (NULL == my_uri) {
        return ORTE_ERROR;
    }
    fprintf(fp, "%s\n", my_uri);
    free(my_uri);

    fprintf(fp, "%lu\n", (unsigned long)orte_process_info.pid);
    fclose(fp);

    return ORTE_SUCCESS;
}
