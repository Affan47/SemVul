term_cursor_color(char_u *color)
{
    if (*T_CSC != NUL)
    {
	out_str(T_CSC);
	out_str_nf(color);
	out_str(T_CEC);
	out_flush();
    }
}
