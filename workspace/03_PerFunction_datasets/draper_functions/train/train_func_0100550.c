NsBlockSignals(int debug)
{
    sigset_t set;


    sigemptyset(&set);
    sigaddset(&set, SIGPIPE);
    sigaddset(&set, SIGTERM);
    sigaddset(&set, SIGHUP);
    if (!nsconf.debug) {

        sigaddset(&set, SIGINT);
    }
    ns_sigmask(SIG_BLOCK, &set, NULL);


    ns_signal(SIGILL, Abort);
    ns_signal(SIGTRAP, Abort);
    ns_signal(SIGBUS, Abort);
    ns_signal(SIGSEGV, Abort);
    ns_signal(SIGFPE, Abort);
}
