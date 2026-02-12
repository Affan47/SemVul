void tty_kclose(struct tty_struct *tty)
{


	tty_ldisc_release(tty);


	tty_flush_works(tty);

	tty_debug_hangup(tty, "freeing structure\n");


	mutex_lock(&tty_mutex);
	tty_port_set_kopened(tty->port, 0);
	release_tty(tty, tty->index);
	mutex_unlock(&tty_mutex);
}
