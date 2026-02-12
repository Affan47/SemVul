static gboolean fork_server(const char *path)
{
    int ret, pid, status;

    if (!g_file_test (MENUCACHE_LIBEXECDIR "/menu-cached", G_FILE_TEST_IS_EXECUTABLE))
    {
        g_error("failed to find menu-cached");
    }


    pid = fork();
    if (pid == 0)
    {
        execl(MENUCACHE_LIBEXECDIR "/menu-cached", MENUCACHE_LIBEXECDIR "/menu-cached",
              path, NULL);
        g_print("failed to exec %s %s\n", MENUCACHE_LIBEXECDIR "/menu-cached", path);
    }


retry_wait:
    ret = waitpid(pid, &status, 0);
    if (ret < 0) {
        if (errno == EINTR)
            goto retry_wait;
    }
    return TRUE;
}
