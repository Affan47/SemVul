check_for_codes_from_term(void)
{
    int		c;


    if (xt_index_out == 0 || xt_index_out == xt_index_in)
	return;


    ++no_mapping;
    ++allow_keys;
    for (;;)
    {
	c = vpeekc();
	if (c == NUL)
	    break;


	if (c != K_SPECIAL && c != K_IGNORE)
	    break;
	c = vgetc();
	if (c != K_IGNORE)
	{
	    vungetc(c);
	    break;
	}
    }
    --no_mapping;
    --allow_keys;
}
