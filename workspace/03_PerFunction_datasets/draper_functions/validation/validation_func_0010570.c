Reject(const char *article, size_t length UNUSED, const char *reason,
       const char *arg)
{
#if	defined(DO_RNEWS_SAVE_BAD)
    char *filename;
    FILE *F;
    int fd;
#endif

    notice(reason, arg);
    if (Verbose) {
	fprintf(stderr, "%s: ", InputFile);
	fprintf(stderr, reason, arg);
	fprintf(stderr, " [%.40s...]\n", article);
    }

#if	defined(DO_RNEWS_SAVE_BAD)
    filename = concat(PathBadNews, "/XXXXXX", (char *) 0);
    fd = mkstemp(filename);
    if (fd < 0) {
        warn("cannot create temporary file");
        return;
    }
    F = fdopen(fd, "w");
    if (F == NULL) {
        warn("cannot fdopen %s", filename);
	return;
    }
    if (fwrite(article, 1, length, F) != length)
        warn("cannot fwrite to %s", filename);
    if (fclose(F) == EOF)
        warn("cannot close %s", filename);
    free(filename);
#endif
}
