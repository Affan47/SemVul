sigalrm_handler(int sig)
{
sig = sig;
sigalrm_seen = TRUE;
os_non_restarting_signal(SIGALRM, sigalrm_handler);
}
