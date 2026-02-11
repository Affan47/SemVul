input_forward(void)
{
	if (cursor < command_len)
		put_cur_glyph_and_inc_cursor();
}
