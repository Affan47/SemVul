clear_termoptions(void)
{


#ifdef FEAT_MOUSE_TTY
    mch_setmouse(FALSE);
#endif
#ifdef FEAT_TITLE
    mch_restore_title(3);
#endif
#if defined(FEAT_XCLIPBOARD) && defined(FEAT_GUI)


    if (gui.starting)
	clear_xterm_clip();
#endif
    stoptermcap();

    free_termoptions();
}
