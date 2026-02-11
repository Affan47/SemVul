iso_gettext (const char *msgid)
{
    static int iso_switch = -1;
    static const char *cset;
    static int cli;
    char *ret;


    if (!strcmp(msgid, "@CLI_INIT")) {
	cli = 1;
	return NULL;
    }

    if (cli) {
	return gettext(msgid);
    }


    if (iso_switch < 0) {

	cset = get_gretl_charset();
	if (cset == NULL) {
	    fprintf(stderr, "get_gretl_charset: using UTF-8\n");
	} else {
	    fprintf(stderr, "get_gretl_charset gave %s\n", cset);
	}
	iso_switch = (cset != NULL);
    }

    if (iso_switch) {
	bind_textdomain_codeset(PACKAGE, cset);
	ret = gettext(msgid);
	bind_textdomain_codeset(PACKAGE, "UTF-8");
    } else {
	ret = gettext(msgid);
    }

    return ret;
}
