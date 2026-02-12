drv_mode(TERMINAL_CONTROL_BLOCK * TCB, int progFlag, int defFlag)
{
    SCREEN *sp;
    TERMINAL *_term = (TERMINAL *) TCB;
    int code = ERR;

    AssertTCB();
    sp = TCB->csp;

    if (progFlag)
    {
	if (defFlag) {


	    if ((drv_sgmode(TCB, FALSE, &(_term->Nttyb)) == OK)) {
#ifdef TERMIOS
		_term->Nttyb.c_oflag &= (unsigned) ~OFLAGS_TABS;
#else
		_term->Nttyb.sg_flags &= (unsigned) ~XTABS;
#endif
		code = OK;
	    }
	} else {

	    if (drv_sgmode(TCB, TRUE, &(_term->Nttyb)) == OK) {
		if (sp) {
		    if (sp->_keypad_on)
			_nc_keypad(sp, TRUE);
		}
		code = OK;
	    }
	}
    } else {
	if (defFlag) {


	    if (drv_sgmode(TCB, FALSE, &(_term->Ottyb)) == OK) {
#ifdef TERMIOS
		if (_term->Ottyb.c_oflag & OFLAGS_TABS)
		    tab = back_tab = NULL;
#else
		if (_term->Ottyb.sg_flags & XTABS)
		    tab = back_tab = NULL;
#endif
		code = OK;
	    }
	} else {

	    if (sp) {
		_nc_keypad(sp, FALSE);
		NCURSES_SP_NAME(_nc_flush) (sp);
	    }
	    code = drv_sgmode(TCB, TRUE, &(_term->Ottyb));
	}
    }
    return (code);
}
