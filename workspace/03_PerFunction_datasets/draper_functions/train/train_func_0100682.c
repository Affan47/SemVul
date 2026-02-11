main(int argc, char *argv[])
{
    fs_gnu_options(argc, argv, "<kbname>\n");

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <kbname>\n", basename(argv[0]));

        return 1;
    }

    const char *kbname = argv[1];

    fs_backend *be = fs_backend_init(kbname, 0);
    if (!be) {
        return 1;
    }

    char *tmp = g_strdup_printf("du -hs "FS_KB_DIR" | sed 's/.\\/var.*/ disk usage/; s/^/  /'", kbname);
    system(tmp);
    g_free(tmp);

    return 0;
}
