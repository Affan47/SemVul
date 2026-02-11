initDefaultHandlers(void)
{
    struct sigaction action,oact;


    action.sa_handler = shutdown_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    if (sigaction(SIGINT, &action, &oact) != 0) {
	sysErrorBelch("warning: failed to install SIGINT handler");
    }

#if defined(HAVE_SIGINTERRUPT)
    siginterrupt(SIGINT, 1);
#endif


#if 0
    action.sa_handler = SIG_IGN;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    if (sigaction(SIGFPE, &action, &oact) != 0) {
	sysErrorBelch("warning: failed to install SIGFPE handler");
    }
#endif

#ifdef alpha_HOST_ARCH
    ieee_set_fp_control(0);
#endif


    action.sa_handler = empty_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    if (sigaction(SIGPIPE, &action, &oact) != 0) {
	sysErrorBelch("warning: failed to install SIGPIPE handler");
    }

    set_sigtstp_action(rtsTrue);
}
