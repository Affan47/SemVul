init_from_dir(const char *dirname, unsigned int max_files)
{
    char filename[1024];
    const gchar *de;
    struct stat stats;
    size_t total;
    int result;
    GDir *dir;

    ENTER("dirname: %s", dirname);
    if (max_files <= 0)
    {
        LEAVE("max_files is 0 or less, skipping directory %s", dirname);
        return 0;
    }

    dir = g_dir_open(dirname, 0, NULL);
    if (dir == NULL)
    {
        LEAVE("unable to open directory %s", dirname);
        return 0;
    }

    total = 0;

    do
    {
        de = g_dir_read_name(dir);
        if (de == NULL)
            break;

        md5_process_bytes(de, strlen(de), &guid_context);
        total += strlen(de);

        result = g_snprintf(filename, sizeof(filename),
                            "%s/%s", dirname, de);
        if ((result < 0) || (result >= (int)sizeof(filename)))
            continue;

        memset(&stats, 0, sizeof(stats));
        if (g_stat(filename, &stats) != 0)
            continue;
        md5_process_bytes(&stats, sizeof(stats), &guid_context);
        total += sizeof(stats);

        max_files--;
    }
    while (max_files > 0);

    g_dir_close(dir);

    LEAVE("");
    return total;
}
