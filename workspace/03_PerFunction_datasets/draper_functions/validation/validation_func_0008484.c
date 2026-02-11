dln_find_exe_r(const char *fname, const char *path, char *buf, size_t size)
{
    char *envpath = 0;

    if (!path) {
	path = getenv(PATH_ENV);
	if (path) path = envpath = strdup(path);
    }

    if (!path) {
#if defined(_WIN32)
	path = "/usr/local/bin;/usr/ucb;/usr/bin;/bin;.";
#else
	path = "/usr/local/bin:/usr/ucb:/usr/bin:/bin:.";
#endif
    }
    buf = dln_find_1(fname, path, buf, size, 1);
    if (envpath) free(envpath);
    return buf;
}
