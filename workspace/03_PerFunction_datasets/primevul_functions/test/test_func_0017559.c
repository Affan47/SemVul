check_shellsize(void)
{
    if (Rows < min_rows())
	Rows = min_rows();
    limit_screen_size();


    if (cmdline_row >= Rows)
	cmdline_row = Rows - 1;
    if (msg_row >= Rows)
	msg_row = Rows - 1;
}
