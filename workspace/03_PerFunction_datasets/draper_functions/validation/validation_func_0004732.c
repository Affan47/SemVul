handle_signal(int sig)
{
	debug(D_DEBUG, "received signal %d: %s", sig, string_signal(sig));
	switch (sig) {
	case SIGINT:
	case SIGTERM:
	case SIGQUIT:
		want_to_exit = 1;
		break;
	case SIGHUP:
		change_state(STATE_STOP_WAIT);
		break;
	}
}
