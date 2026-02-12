NCURSES_SP_NAME(ungetmouse) (NCURSES_SP_DCLx MEVENT * aevent)
{
    int result = ERR;
    MEVENT *eventp;

    T((T_CALLED("ungetmouse(%p,%p)"), (void *) SP_PARM, (void *) aevent));

    if (aevent != 0 &&
	SP_PARM != 0 &&
	(eventp = SP_PARM->_mouse_eventp) != 0) {


	*eventp = *aevent;


	SP_PARM->_mouse_eventp = NEXT(eventp);


	result = NCURSES_SP_NAME(ungetch) (NCURSES_SP_ARGx KEY_MOUSE);
    }
    returnCode(result);
}
