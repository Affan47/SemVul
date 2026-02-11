do_eof(char c)
{
	if (backslashed) {
		lbptr--;
		ansi_process_s("\b");
		do_data(c);
		return;
	}
	if (lnext) {
		do_data(c);
		return;
	}
	do_data(c);
	forward_data();
}
