static void lp_detach (struct parport *port)
{

#ifdef CONFIG_LP_CONSOLE
	if (console_registered == port) {
		unregister_console(&lpcons);
		console_registered = NULL;
	}
#endif
}
