stuff_inserted(
    int	    c,
    long    count,
    int	    no_esc)
{
    char_u	*esc_ptr;
    char_u	*ptr;
    char_u	*last_ptr;
    char_u	last = NUL;

    ptr = get_last_insert();
    if (ptr == NULL)
    {
	emsg(_(e_no_inserted_text_yet));
	return FAIL;
    }


    if (c != NUL)
	stuffcharReadbuff(c);
    if ((esc_ptr = (char_u *)vim_strrchr(ptr, ESC)) != NULL)
	*esc_ptr = NUL;


    last_ptr = (esc_ptr ? esc_ptr : ptr + STRLEN(ptr)) - 1;
    if (last_ptr >= ptr && (*last_ptr == '0' || *last_ptr == '^')
	    && (no_esc || (*ptr == Ctrl_D && count > 1)))
    {
	last = *last_ptr;
	*last_ptr = NUL;
    }

    do
    {
	stuffReadbuff(ptr);

	if (last)
	    stuffReadbuff((char_u *)(last == '0'
			? IF_EB("\026\060\064\070", CTRL_V_STR "xf0")
			: IF_EB("\026^", CTRL_V_STR "^")));
    }
    while (--count > 0);

    if (last)
	*last_ptr = last;

    if (esc_ptr != NULL)
	*esc_ptr = ESC;


    if (!no_esc)
	stuffcharReadbuff(ESC);

    return OK;
}
