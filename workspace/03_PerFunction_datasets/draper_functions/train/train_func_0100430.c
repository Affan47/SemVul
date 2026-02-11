read_parameter_file(void)
{
#if !defined(_WIN32) || defined(cygwin)
    char *name;
    struct passwd *pw;
#endif

    read_parameter_file_1(PARAMETER_FILE);
#if !defined(_WIN32) || defined(cygwin)
    pw = getpwuid(getuid());
    if ( pw == NULL )
        fatal("getpwuid() failed for uid: %d\n", getuid());
    name = xmalloc(strlen(pw->pw_dir) + strlen(PARAMETER_DOTFILE) + 2);
    strcpy(name, pw->pw_dir);
    strcat(name, "/" PARAMETER_DOTFILE);
    read_parameter_file_1(name);
    free(name);
#endif
}
