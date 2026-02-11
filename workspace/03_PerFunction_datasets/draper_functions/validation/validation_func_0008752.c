tgdb_setup_config_file(struct annotate_two *a2, const char *dir)
{
    FILE *fp;

    strncpy(a2->config_dir, dir, strlen(dir) + 1);

    fs_util_get_path(dir, "a2_gdb_init", a2->a2_gdb_init_file);

    if ((fp = fopen(a2->a2_gdb_init_file, "w"))) {
        fprintf(fp, "set annotate 2\n" "set height 0\n");
        fclose(fp);
    } else {
        logger_write_pos(logger, __FILE__, __LINE__, "fopen error '%s'",
                a2->a2_gdb_init_file);
        return 0;
    }

    return 1;
}
