skip_msgid (const char **in)
{
	const char *inptr = *in;

	decode_lwsp (&inptr);
	if (*inptr == '<') {
		inptr++;
		skip_addrspec (&inptr);
		if (*inptr == '>')
			inptr++;
	} else {
		skip_atom (&inptr);
	}

	*in = inptr;
}
