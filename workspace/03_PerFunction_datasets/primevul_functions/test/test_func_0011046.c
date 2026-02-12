allow_gpm_mouse(SCREEN *sp GCC_UNUSED)
{
    bool result = FALSE;

#if USE_WEAK_SYMBOLS

    if ((Gpm_Wgetch) != 0) {
	if (!sp->_mouse_gpm_loaded) {
	    T(("GPM library was already dlopen'd, not by us"));
	}
    } else
#endif

    if (NC_ISATTY(fileno(stdout))) {
	const char *list = getenv("NCURSES_GPM_TERMS");
	const char *env = getenv("TERM");
	if (list != 0) {
	    if (env != 0) {
		result = _nc_name_match(list, env, "|:");
	    }
	} else {


	    if (env != 0 && strstr(env, "linux") != 0) {
		result = TRUE;
	    }
	}
    }
    return result;
}
