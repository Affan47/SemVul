my_usage(const char *progname, const struct my_option *opt)
{
    int i;
    size_t col = 0;

    fprintf(stdout, "Usage: %s", progname);
    col += (strlen(progname) + 7);
    for (i = 0; opt[i].long_name; i++) {
	size_t option_len;

	option_len = strlen(opt[i].long_name);
	if (col >= 80 - (option_len + 16)) {
	    fputs("\n\t", stdout);
	    col = 8;
	}
	fprintf(stdout, " [--%s", opt[i].long_name);
	col += (option_len + 4);
	if (opt[i].short_name < 128) {
	    fprintf(stdout, " | -%c", opt[i].short_name);
	    col += 5;
	}
	switch (opt[i].argtype) {
	    case REQARG:
		 fputs(" arg]", stdout);
		 col += 5;
		 break;
	    case OPTARG:
		 fputs(" [arg]]", stdout);
		 col += 10;
		 break;
	    default:
		 fputs("]", stdout);
		 col++;
	}
    }

    fputs ("\n", stdout);
}
