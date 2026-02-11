main(int argc, char** argv)
{
    Conf *conf = read_conf();


    if (!check_spool_dir(conf))
        exit(1);


    char *sp;
    if (asprintf(&sp, "%s%s%s%sXXXXXXXXXX", conf->spool_dir, DIR_SEP, MSGS_DIR,
      DIR_SEP) == -1) {
        errx(1, "main: asprintf: unable to allocate memory");
    }

    int sfd;
    if ((sfd = mkstemp(sp)) == -1)
        err(1, "mkstemp: when creating spool file %s", sp);


    if (flock(sfd, LOCK_EX) == -1)
        err(1, "flock: when locking spool file %s", sp);


    FILE *sf;
    if ((sf = fdopen(sfd, "w")) == NULL)
        err(1, "main: fdopen");

#   define SPOOL_WRITE(fmt, args...) if (fprintf(sf, fmt, ##args) == -1) \
        err(1, "%s: When writing to spool file", sp)


    SPOOL_WRITE("%s\n", VERSION1_ID);


    SPOOL_WRITE("%d\n", argc - 1);

    for (int i = 1; i < argc; i += 1)
        SPOOL_WRITE("%zd\n%s\n", strlen(argv[i]), argv[i]);

#   define BUF_SIZE 1024

    char buf[BUF_SIZE];
    size_t total_nr = 0;
    while (1) {
        size_t nr;
        if ((nr = fread(buf, 1, BUF_SIZE, stdin)) < BUF_SIZE
          && ferror(stdin)) {
            errx(1, "main: ferror");
        }

        if (fwrite(buf, 1, nr, sf) < nr)
            errx(1, "main: fwrite: when writing to spool file");

        total_nr += nr;

        if (feof(stdin) != 0)
            break;
    }

    fflush(sf);
    fclose(sf);


    if (total_nr == 0)
        unlink(sp);

    flock(sfd, LOCK_UN);
    close(sfd);

    return 0;
}
