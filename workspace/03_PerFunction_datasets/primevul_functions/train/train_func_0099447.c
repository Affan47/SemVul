mch_msg(char *str)
{
#if (defined(UNIX) || defined(FEAT_GUI)) && !defined(ALWAYS_USE_GUI) && !defined(VIMDLL)


    if (
# ifdef UNIX
#  ifdef MACOS_X
	    (isatty(2) && strcmp("/dev/console", ttyname(2)) != 0)
#  else
	    isatty(2)
#  endif
#  ifdef FEAT_GUI
	    ||
#  endif
# endif
# ifdef FEAT_GUI
	    !(gui.in_use || gui.starting)
# endif
	    )
    {
	printf("%s", str);
	return;
    }
#endif

#if defined(MSWIN) && (!defined(FEAT_GUI_MSWIN) || defined(VIMDLL))
# ifdef VIMDLL
    if (!(gui.in_use || gui.starting))
# endif
    {
	mch_msg_c(str);
	return;
    }
#endif
#if !defined(MSWIN) || defined(FEAT_GUI_MSWIN)
    mch_errmsg(str);
#endif
}
