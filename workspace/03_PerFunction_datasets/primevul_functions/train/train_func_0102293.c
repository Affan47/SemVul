static int check_tty(struct tty_struct *tty)
{
	if (!tty) {
		pr_warn("%s: I/O error, deactivating speakup\n",
			spk_ttyio_synth->long_name);


		spk_ttyio_synth->alive = 0;
		speakup_start_ttys();
		return 1;
	}

	return 0;
}
