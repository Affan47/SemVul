translate_signal( int sig )
{
#define DEFSIG(s) case s: return #s
    switch( sig ) {
        DEFSIG(SIGHUP);
        DEFSIG(SIGINT);
        DEFSIG(SIGQUIT);
        DEFSIG(SIGILL);
        DEFSIG(SIGABRT);
        DEFSIG(SIGFPE);
        DEFSIG(SIGKILL);
        DEFSIG(SIGSEGV);
        DEFSIG(SIGPIPE);
        DEFSIG(SIGALRM);
        DEFSIG(SIGTERM);
        DEFSIG(SIGUSR1);
        DEFSIG(SIGUSR2);
        DEFSIG(SIGCHLD);
        DEFSIG(SIGCONT);
        DEFSIG(SIGSTOP);
        DEFSIG(SIGTSTP);
        DEFSIG(SIGTTIN);
        DEFSIG(SIGTTOU);
        DEFSIG(SIGBUS);
        DEFSIG(SIGPOLL);
        DEFSIG(SIGPROF);
        DEFSIG(SIGSYS);
        DEFSIG(SIGTRAP);
        DEFSIG(SIGURG);
        DEFSIG(SIGVTALRM);
        DEFSIG(SIGXCPU);
        DEFSIG(SIGXFSZ);
    default:
        {
            static char buffer[50];
            sprintf( buffer, "signal %d", sig );

            return buffer;
        }
    }
}
