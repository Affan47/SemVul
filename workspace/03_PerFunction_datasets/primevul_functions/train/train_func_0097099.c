int linenoiseHistorySave(const char* filename) {
    FILE* fp;
#if _POSIX_C_SOURCE >= 1 || _XOPEN_SOURCE || _POSIX_SOURCE
    int fd = open(filename, O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {

        return -1;
    }
    fp = fdopen(fd, "wt");
#else
    fp = fopen(filename, "wt");
#endif
    if (fp == NULL) {
        return -1;
    }

    for (int j = 0; j < historyLen; ++j) {
        if (history[j][0] != '\0') {
            fprintf(fp, "%s\n", history[j]);
        }
    }
    fclose(fp);
    return 0;
}
