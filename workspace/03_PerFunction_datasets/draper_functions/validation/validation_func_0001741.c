redirect_to_script(char *script)
{
    char urlbuf[BIG_LINE];
    char *ptr;

    PR_snprintf(urlbuf, sizeof(urlbuf), "%s%s", getenv("SERVER_URL"), getenv("SCRIPT_NAME"));
    if ((ptr = strrchr(urlbuf, '/'))) {
        int maxsize = sizeof(urlbuf)-((ptr-urlbuf)+2);
        PL_strncpyz(ptr + 1, script, maxsize);
    } else {
        PR_snprintf(urlbuf, sizeof(urlbuf), "%s/%s", getenv("SERVER_URL"), script);
    }
    printf("Location: %s\n\n", urlbuf);
}
