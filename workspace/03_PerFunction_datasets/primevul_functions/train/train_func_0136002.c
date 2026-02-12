static void fn_hold(struct vc_data *vc)
{
	struct tty_struct *tty = vc->port.tty;

	if (rep || !tty)
		return;


	if (tty->stopped)
		start_tty(tty);
	else
		stop_tty(tty);
}
