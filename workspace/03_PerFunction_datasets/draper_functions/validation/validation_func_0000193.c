dump_pid (void)
{
    FILE   *f;
    char    path[_POSIX_PATH_MAX];

    log_message ("dump_pid: pid is %d", getpid ());
    snprintf (path, sizeof (path), "%s/pid", Config_Dir);
    f = fopen (path, "w");
    if (!f)
    {
	logerr ("dump_pid", path);
	return;
    }
    fprintf (f, "%d\n", (int) getpid ());
    fclose (f);
}
