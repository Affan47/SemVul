open_procnetdev(void)
{
    FILE *fd;
    char buf[161];

    fd = fopen("/proc/net/dev", "r");


    if (fd != NULL) {
        fgets(buf, 160, fd);
        fgets(buf, 160, fd);
    }

    return fd;
}
