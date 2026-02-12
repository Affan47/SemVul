cursor_off(void)
{
    if (full_screen && !cursor_is_off)
    {
	out_str(T_VI);
	cursor_is_off = TRUE;
    }
}
