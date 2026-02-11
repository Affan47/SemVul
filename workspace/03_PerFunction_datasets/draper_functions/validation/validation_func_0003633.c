is_char_ok(signed char c, gint base)
{

	if(base == 0)
		return TRUE;


	if(isalpha(c))
		c = toupper(c) - 'A' + '9' + 1;
	else if(!isdigit(c))
		return FALSE;

	c = c - '0';

	return((c < 0) ||(c >(base - 1))) ? FALSE : TRUE;
}
