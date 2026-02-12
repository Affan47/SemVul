NCURSES_SP_NAME(_nc_mvcur_wrap) (NCURSES_SP_DCL0)

{

    TINFO_MVCUR(NCURSES_SP_ARGx -1, -1, screen_lines(SP_PARM) - 1, 0);

    if (!SP_PARM || !IsTermInfo(SP_PARM))
	return;


    if (SP_PARM->_cursor != -1) {
	int cursor = SP_PARM->_cursor;
	NCURSES_SP_NAME(curs_set) (NCURSES_SP_ARGx 1);
	SP_PARM->_cursor = cursor;
    }

    if (exit_ca_mode) {
	NCURSES_PUTP2("exit_ca_mode", exit_ca_mode);
    }


    NCURSES_SP_NAME(_nc_outch) (NCURSES_SP_ARGx '\r');
}
