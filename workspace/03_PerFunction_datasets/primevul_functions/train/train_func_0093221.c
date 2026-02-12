SendLocatorPosition(XtermWidget xw, XButtonEvent *event)
{
    ANSI reply;
    TScreen *screen = TScreenOf(xw);
    int row, col;
    Bool oor;
    int button;
    unsigned state;


    if (IsBtnEvent(event)) {
	if (OverrideButton(event))
	    return (False);
    } else {
	if (!screen->loc_filter)
	    return (False);
    }

    if ((event->type == ButtonPress &&
	 !(screen->locator_events & LOC_BTNS_DN)) ||
	(event->type == ButtonRelease &&
	 !(screen->locator_events & LOC_BTNS_UP)))
	return (True);

    if (event->type == MotionNotify) {
	CheckLocatorPosition(xw, event);
	return (True);
    }


    button = (int) event->button - 1;

    LocatorCoords(row, col, event->x, event->y, oor);


    memset(&reply, 0, sizeof(reply));
    reply.a_type = ANSI_CSI;

    if (oor) {
	reply.a_nparam = 1;
	reply.a_param[0] = 0;
	reply.a_inters = '&';
	reply.a_final = 'w';
	unparseseq(xw, &reply);

	if (screen->locator_reset) {
	    MotionOff(screen, xw);
	    screen->send_mouse_pos = MOUSE_OFF;
	}
	return (True);
    }


    reply.a_nparam = 4;
    switch (event->type) {
    case ButtonPress:
	reply.a_param[0] = (ParmType) (2 + (button << 1));
	break;
    case ButtonRelease:
	reply.a_param[0] = (ParmType) (3 + (button << 1));
	break;
    default:
	return (True);
    }


    state = (event->state
	     & (Button1Mask | Button2Mask | Button3Mask | Button4Mask)) >> 8;

    state ^= ((unsigned) (1 << button));

    state = ((state & (unsigned) ~(4 | 1))
	     | ((state & 1) ? 4 : 0)
	     | ((state & 4) ? 1 : 0));

    reply.a_param[1] = (ParmType) state;
    reply.a_param[2] = (ParmType) row;
    reply.a_param[3] = (ParmType) col;
    reply.a_inters = '&';
    reply.a_final = 'w';

    unparseseq(xw, &reply);

    if (screen->locator_reset) {
	MotionOff(screen, xw);
	screen->send_mouse_pos = MOUSE_OFF;
    }


    if (screen->loc_filter) {
	screen->send_mouse_pos = MOUSE_OFF;
	screen->loc_filter = False;
	screen->locator_events = 0;
	MotionOff(screen, xw);
    }

    return (True);
}
