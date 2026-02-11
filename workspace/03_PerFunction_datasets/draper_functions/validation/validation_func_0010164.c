ahc_parse_brace_option(char *opt_name, char *opt_arg, char *end, int depth,
		       void (*callback)(u_long, int, int, int32_t),
		       u_long callback_arg)
{
	char	*tok_end;
	char	*tok_end2;
	int      i;
	int      instance;
	int	 targ;
	int	 done;
	char	 tok_list[] = {'.', ',', '{', '}', '\0'};


	if (*opt_arg != ':')
		return (opt_arg);
	opt_arg++;
	instance = -1;
	targ = -1;
	done = FALSE;


	tok_end = strchr(opt_arg, '\0');
	if (tok_end < end)
		*tok_end = ',';
	while (!done) {
		switch (*opt_arg) {
		case '{':
			if (instance == -1) {
				instance = 0;
			} else {
				if (depth > 1) {
					if (targ == -1)
						targ = 0;
				} else {
					printk("Malformed Option %s\n",
					       opt_name);
					done = TRUE;
				}
			}
			opt_arg++;
			break;
		case '}':
			if (targ != -1)
				targ = -1;
			else if (instance != -1)
				instance = -1;
			opt_arg++;
			break;
		case ',':
		case '.':
			if (instance == -1)
				done = TRUE;
			else if (targ >= 0)
				targ++;
			else if (instance >= 0)
				instance++;
			opt_arg++;
			break;
		case '\0':
			done = TRUE;
			break;
		default:
			tok_end = end;
			for (i = 0; tok_list[i]; i++) {
				tok_end2 = strchr(opt_arg, tok_list[i]);
				if ((tok_end2) && (tok_end2 < tok_end))
					tok_end = tok_end2;
			}
			callback(callback_arg, instance, targ,
				 simple_strtol(opt_arg, NULL, 0));
			opt_arg = tok_end;
			break;
		}
	}
	return (opt_arg);
}
