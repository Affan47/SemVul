NCURSES_SP_NAME(getmouse) (NCURSES_SP_DCLx MEVENT * aevent)
{
    int result = ERR;
    MEVENT *eventp;

    T((T_CALLED("getmouse(%p,%p)"), (void *) SP_PARM, (void *) aevent));

    if ((aevent != 0) &&
	(SP_PARM != 0) &&
	(SP_PARM->_mouse_type != M_NONE) &&
	(eventp = SP_PARM->_mouse_eventp) != 0) {

	MEVENT *prev = PREV(eventp);


	while (ValidEvent(prev) && (!(prev->bstate & SP_PARM->_mouse_mask2))) {
	    Invalidate(prev);
	    prev = PREV(prev);
	}
	if (ValidEvent(prev)) {

	    *aevent = *prev;

	    TR(TRACE_IEVENT, ("getmouse: returning event %s from slot %ld",
			      _nc_tracemouse(SP_PARM, prev),
			      (long) IndexEV(SP_PARM, prev)));

	    Invalidate(prev);
	    SP_PARM->_mouse_eventp = prev;
	    result = OK;
	} else {

	    aevent->bstate = 0;
	    Invalidate(aevent);
	    aevent->x = 0;
	    aevent->y = 0;
	    aevent->z = 0;
	}
    }
    returnCode(result);
}
