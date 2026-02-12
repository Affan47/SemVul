help_command()
{
    static char *helpbuf = NULL;
    static char *prompt = NULL;
    static int toplevel = 1;
    int base;
    int len;
    TBOOLEAN more_help;
    TBOOLEAN only;
    TBOOLEAN subtopics;
    int start;
    char *help_ptr;
# if defined(SHELFIND)
    static char help_fname[256] = "";
# endif

    if ((help_ptr = getenv("GNUHELP")) == (char *) NULL)
# ifndef SHELFIND

#  if defined(MSDOS) || defined(OS2)
	help_ptr = HelpFile;
#  else
	help_ptr = HELPFILE;
#  endif

# else


    if (!strchr(HELPFILE, ':') && !strchr(HELPFILE, '/') &&
	!strchr(HELPFILE, '\\')) {
	if (strlen(help_fname) == 0) {
	    strcpy(help_fname, HELPFILE);
	    if (shel_find(help_fname) == 0) {
		strcpy(help_fname, HELPFILE);
	    }
	}
	help_ptr = help_fname;
    } else {
	help_ptr = HELPFILE;
    }
# endif


    if (helpbuf == NULL) {
	helpbuf = gp_alloc(MAX_LINE_LEN, "help buffer");
	prompt = gp_alloc(MAX_LINE_LEN, "help prompt");
	helpbuf[0] = prompt[0] = 0;
    }
    if (toplevel)
	helpbuf[0] = prompt[0] = 0;


    toplevel = 1;

    len = base = strlen(helpbuf);

    start = ++c_token;


    while (!(END_OF_COMMAND))
	c_token++;


    if (len > 0)
	helpbuf[len++] = ' ';
    capture(helpbuf + len, start, c_token - 1, MAX_LINE_LEN - len);
    squash_spaces(helpbuf + base, 1);
    len = strlen(helpbuf);


    if (strcmp(helpbuf + (base ? base + 1 : 0), "?") == 0) {

	subtopics = 1;
	only = TRUE;
	helpbuf[base] = NUL;
    } else {

	subtopics = 0;
	only = FALSE;
    }

    switch (help(helpbuf, help_ptr, &subtopics)) {
    case H_FOUND:{


	    screen_ok = FALSE;

	    do {
		if (subtopics && !only) {

		    if (len > 0) {
			strcpy (prompt, "Subtopic of ");
			strncat (prompt, helpbuf, MAX_LINE_LEN - 16);
			strcat (prompt, ": ");
		    } else
			strcpy(prompt, "Help topic: ");
		    read_line(prompt, 0);
		    num_tokens = scanner(&gp_input_line, &gp_input_line_len);
		    c_token = 0;
		    more_help = !(END_OF_COMMAND);
		    if (more_help) {
			c_token--;
			toplevel = 0;

			help_command();
		    }
		} else
		    more_help = FALSE;
	    } while (more_help);

	    break;
	}
    case H_NOTFOUND:
	printf("Sorry, no help for '%s'\n", helpbuf);
	break;
    case H_ERROR:
	perror(help_ptr);
	break;
    default:
	int_error(NO_CARET, "Impossible case in switch");
	break;
    }

    helpbuf[base] = NUL;
}
