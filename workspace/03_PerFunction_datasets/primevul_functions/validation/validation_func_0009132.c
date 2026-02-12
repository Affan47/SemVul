void tty_release_struct(struct tty_struct *tty, int idx)
{


	tty_ldisc_release(tty);


	tty_flush_works(tty);

	tty_debug_hangup(tty, "freeing structure\n");


	mutex_lock(&tty_mutex);
	release_tty(tty, idx);
	mutex_unlock(&tty_mutex);
}
