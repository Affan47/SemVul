init_terminal()
{
    char *term_name = DEFAULTTERM;
#if defined(__BEOS__) || defined(X11)
    char *env_term = NULL;
#endif
#ifdef X11
    char *display = NULL;
#endif
    char *gnuterm = NULL;


    gnuterm = getenv("GNUTERM");
    if (gnuterm != (char *) NULL) {

	char *set_term = "set term ";
	char *set_term_command = gp_alloc(strlen(set_term) + strlen(gnuterm) + 4, NULL);
	strcpy(set_term_command, set_term);
	strcat(set_term_command, gnuterm);
	do_string(set_term_command);
	free(set_term_command);

	Gstring(&(add_udv_by_name("GNUTERM")->udv_value), gp_strdup(gnuterm));
	return;

    } else {

#ifdef VMS
	term_name = vms_init();
#endif

	if (term_name == (char *) NULL
            && getenv ("DOMTERM") != NULL)
          term_name = "domterm";

#ifdef __BEOS__
	env_term = getenv("TERM");
	if (term_name == (char *) NULL
	    && env_term != (char *) NULL && strcmp(env_term, "beterm") == 0)
	    term_name = "be";
#endif

#ifdef QTTERM
	if (term_name == (char *) NULL)
	    term_name = "qt";
#endif

#ifdef WXWIDGETS
	if (term_name == (char *) NULL)
	    term_name = "wxt";
#endif

#ifdef _WIN32
	if (term_name == (char *) NULL)
	    term_name = "win";
#endif

#if defined(__APPLE__) && defined(__MACH__) && defined(HAVE_FRAMEWORK_AQUATERM)

	term_name = "aqua";
#endif

#ifdef X11
	env_term = getenv("TERM");
	if (term_name == (char *) NULL
	    && env_term != (char *) NULL && strcmp(env_term, "xterm") == 0)
	    term_name = "x11";
	display = getenv("DISPLAY");
	if (term_name == (char *) NULL && display != (char *) NULL)
	    term_name = "x11";
	if (X11_Display)
	    term_name = "x11";
#endif

#ifdef DJGPP
	term_name = "svga";
#endif

#ifdef GRASS
	term_name = "grass";
#endif

#ifdef OS2


#ifdef X11


	env_term = getenv("WINDOWID");
	display  = getenv("DISPLAY");
	if ((env_term != (char *) NULL) && (display != (char *) NULL))
	    term_name = "x11";
	else
#endif
	    term_name = "pm";
#endif

    }


    if (term_name != NULL && *term_name != '\0') {
	int namelength = strlen(term_name);
	struct udvt_entry *name = add_udv_by_name("GNUTERM");

	Gstring(&name->udv_value, gp_strdup(term_name));

	if (strchr(term_name,' '))
	    namelength = strchr(term_name,' ') - term_name;


	if (change_term(term_name, namelength)) {
	    if (strcmp(term->name,"x11"))
		term->options();
	    return;
	}
	fprintf(stderr, "Unknown or ambiguous terminal name '%s'\n", term_name);
    }
    change_term("unknown", 7);
}
