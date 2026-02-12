term_start_plot()
{
    FPRINTF((stderr, "term_start_plot()\n"));

    if (!term_initialised)
	term_initialise();

    if (!term_graphics) {
	FPRINTF((stderr, "- calling term->graphics()\n"));
	(*term->graphics) ();
	term_graphics = TRUE;
    } else if (multiplot && term_suspended) {
	if (term->resume) {
	    FPRINTF((stderr, "- calling term->resume()\n"));
	    (*term->resume) ();
	}
	term_suspended = FALSE;
    }

    if (multiplot)
	multiplot_count++;


    (*term->layer)(TERM_LAYER_RESET);


    if (term->flags & TERM_IS_POSTSCRIPT)
	invalidate_palette();


	canvas.xleft  = 0;
	canvas.xright = term->xmax - 1;
	canvas.ybot   = 0;
	canvas.ytop   = term->ymax - 1;

}
