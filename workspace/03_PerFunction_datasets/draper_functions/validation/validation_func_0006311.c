new_arg_length(Namep arg)
#endif
{
	static char buf[64];
	char *fmt = "%s_len", *s = arg->fvarname;
	switch(*s) {
	  case 'r':
		if (!strcmp(s+1, "et_val"))
			goto adjust_fmt;
		break;
	  case 'h':
	  case 'i':
		if (!s[1]) {
 adjust_fmt:
			fmt = "%s_length";
			}
	  }
	sprintf (buf, fmt, s);
	return buf;
}
