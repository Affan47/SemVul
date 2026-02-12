term_end_plot()
{
    FPRINTF((stderr, "term_end_plot()\n"));

    if (!term_initialised)
	return;


    (*term->layer)(TERM_LAYER_END_TEXT);

    if (!multiplot) {
	FPRINTF((stderr, "- calling term->text()\n"));
	(*term->text) ();
	term_graphics = FALSE;
    } else {
	multiplot_next();
    }

#ifdef VMS
    if (opened_binary)
	fflush_binary();
    else
#endif
	(void) fflush(gpoutfile);

#ifdef USE_MOUSE
    if (term->set_ruler) {
	recalc_statusline();
	update_ruler();
    }
#endif
}
