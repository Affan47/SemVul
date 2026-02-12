term_reset()
{
    FPRINTF((stderr, "term_reset()\n"));

#ifdef USE_MOUSE

    paused_for_mouse = 0;
#ifdef _WIN32
    kill_pending_Pause_dialog();
#endif
#endif

    if (!term_initialised)
	return;

    if (term_suspended) {
	if (term->resume) {
	    FPRINTF((stderr, "- calling term->resume()\n"));
	    (*term->resume) ();
	}
	term_suspended = FALSE;
    }
    if (term_graphics) {
	(*term->text) ();
	term_graphics = FALSE;
    }
    if (term_initialised) {
	(*term->reset) ();
	term_initialised = FALSE;

	gppsfile = NULL;
    }
}
