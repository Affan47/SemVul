HandleSelectExtend(Widget w,
		   XEvent *event,
		   String *params GCC_UNUSED,
		   Cardinal *num_params GCC_UNUSED)
{
    XtermWidget xw;

    if ((xw = getXtermWidget(w)) != 0) {
	TScreen *screen = TScreenOf(xw);
	CELL cell;

	TRACE_EVENT("HandleSelectExtend", event, params, num_params);

	screen->selection_time = event->xmotion.time;
	switch (screen->eventMode) {

	case LEFTEXTENSION:
	case RIGHTEXTENSION:
	    PointToCELL(screen, event->xmotion.y, event->xmotion.x, &cell);
	    ExtendExtend(xw, &cell);
	    break;


	case NORMAL:

	    if (okSendMousePos(xw) == BTN_EVENT_MOUSE
		|| okSendMousePos(xw) == ANY_EVENT_MOUSE) {
		(void) SendMousePosition(xw, event);
	    }
	    break;
	}
    }
}
