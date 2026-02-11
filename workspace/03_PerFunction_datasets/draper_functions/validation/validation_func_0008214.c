daemonize(int fd) {
    if(global_options.option.foreground)
        return 0;
    dup2(fd, 0);
    dup2(fd, 1);
    dup2(fd, 2);
#if defined(HAVE_DAEMON) && !defined(__BEOS__)


    if(daemon(0, 1)==-1) {
        ioerror("daemon");
        return 1;
    }
#else
    chdir("/");
    switch(fork()) {
    case -1:
        ioerror("fork");
        return 1;
    case 0:
        break;
    default:
        exit(0);
    }
#endif
#ifdef HAVE_SETSID
    setsid();
#endif
    return 0;
}
