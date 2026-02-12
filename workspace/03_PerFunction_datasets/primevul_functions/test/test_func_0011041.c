wrap_cursor(NCURSES_SP_DCL0)
{
    if (eat_newline_glitch) {


	SP_PARM->_curscol = -1;
	SP_PARM->_cursrow = -1;
    } else if (auto_right_margin) {
	SP_PARM->_curscol = 0;
	SP_PARM->_cursrow++;


	if (!move_standout_mode && AttrOf(SCREEN_ATTRS(SP_PARM))) {
	    TR(TRACE_CHARPUT, ("turning off (%#lx) %s before wrapping",
			       (unsigned long) AttrOf(SCREEN_ATTRS(SP_PARM)),
			       _traceattr(AttrOf(SCREEN_ATTRS(SP_PARM)))));
	    VIDPUTS(SP_PARM, A_NORMAL, 0);
	}
    } else {
	SP_PARM->_curscol--;
    }
    position_check(NCURSES_SP_ARGx
		   SP_PARM->_cursrow,
		   SP_PARM->_curscol,
		   "wrap_cursor");
}
