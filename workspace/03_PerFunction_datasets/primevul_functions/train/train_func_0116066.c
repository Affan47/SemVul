static char *get_argv1_if_full_path(const char* cmdline)
{
    const char *argv1 = strchr(cmdline, ' ');
    while (argv1 != NULL)
    {


        argv1++;
        if (*argv1 != '-')
            break;

        argv1 = strchr(argv1, ' ');
    }


    if (argv1 == NULL || *argv1 != '/')
        return NULL;


    int len = strchrnul(argv1, ' ') - argv1;
    return xstrndup(argv1, len);
}
