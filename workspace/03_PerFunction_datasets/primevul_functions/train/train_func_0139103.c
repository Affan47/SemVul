imapx_server_child_process_setup (gpointer user_data)
{
#ifdef TIOCNOTTY
	gint fd;
#endif

	setsid ();

#ifdef TIOCNOTTY


	if ((fd = open ("/dev/tty", O_RDONLY)) != -1) {
		ioctl (fd, TIOCNOTTY, NULL);
		close (fd);
	}
#endif
}
