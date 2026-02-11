proctitle_init(int argc, char *argv[], char *envp[]) {
    register int i, envpsize;
    char **p;


    for ( i = envpsize = 0; envp[i] != NULL; i++ ) {
        envpsize += strlen(envp[i]) + 1;
    }

    if ((p = (char **) malloc((i + 1) * sizeof(char *))) != NULL) {
        environ = p;

        for (i = 0; envp[i] != NULL; i++) {
            if ((environ[i] = static_cast<char *>(malloc(strlen(envp[i]) + 1))) != NULL) {
                strcpy(environ[i], envp[i]);
            }
        }

        environ[i] = NULL;
    }

    Argv = argv;

# if PF_ARGV_TYPE == PF_ARGV_WRITEABLE
    for (i = 0; i < argc; i++) {
        if (!i || (LastArgv + 1 == argv[i])) {
            LastArgv = argv[i] + strlen(argv[i]);
        }
    }
    cleanUpTo = LastArgv;

    for (i = 0; envp[i] != NULL; i++) {

        if (!strncmp(envp[i], "XDG_", 4))
            break;
        if ((LastArgv + 1) == envp[i]) {
            LastArgv = envp[i] + strlen(envp[i]);
        }
    }
#endif

# ifdef HAVE___PROGNAME


    __progname = strdup("kdeinit4");
# endif
# ifdef HAVE___PROGNAME_FULL

    __progname_full = strdup(argv[0]);
# endif
}
