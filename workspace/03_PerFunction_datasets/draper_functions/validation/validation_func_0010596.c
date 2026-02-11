gsync_status (char *master, char *slave, int *status)
{
        char pidfile[PATH_MAX] = {0,};
        int  fd                = -1;

        fd = gsyncd_getpidfile (master, slave, pidfile);
        if (fd == -2)
                return -1;

        *status = gsync_status_byfd (fd);

        close (fd);
        return 0;
}
