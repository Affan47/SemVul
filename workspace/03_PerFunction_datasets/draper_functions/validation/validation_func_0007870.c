stat_to_pid(explain_string_buffer_t *sb, const struct stat *st)
{
#ifdef TRY_PROC_FIRST
    int             count;
    DIR             *dp;

    count = 0;
    dp = opendir("/proc");
    if (!dp)
        return -1;
    for (;;)
    {
        struct dirent *dep;
        char          *ep;
        int           pid;

        dep = readdir(dp);
        if (!dep)
            break;
        ep = 0;
        pid = strtol(dep->d_name, &ep, 10);
        if (ep == dep->d_name || *ep)
            continue;
        if (snoop_process(pid, st))
        {
            if (count == 0)
                explain_string_buffer_puts(sb, " (pid");
            else
                explain_string_buffer_putc(sb, ',');
            explain_string_buffer_printf(sb, " %d", pid);
            ++count;
        }
    }
    closedir(dp);
    if (count > 0)
        explain_string_buffer_putc(sb, ')');
    return count;
#else
    adapter         obj;

    obj.st = st;
    obj.inherited.n_callback = n_callback;
    obj.sb = sb;
    obj.count = 0;
    obj.caption = 0;
    explain_lsof("", &obj.inherited);
    if (obj.count > 0)
        explain_string_buffer_putc(sb, ')');
    return obj.count;
#endif
}
