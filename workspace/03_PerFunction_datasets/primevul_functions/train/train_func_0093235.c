ReadLineButton(Widget w,
	       XEvent *event,
	       String *params,
	       Cardinal *num_params)
{
    XtermWidget xw;

    if ((xw = getXtermWidget(w)) != 0) {
	TScreen *screen = TScreenOf(xw);
	Char Line[6];
	int line, col, ldelta = 0;

	if (!IsBtnEvent(event)
	    || (okSendMousePos(xw) != MOUSE_OFF) || ExtendingSelection)
	    goto finish;
	if (event->type == ButtonRelease) {
	    int delta;

	    if (lastButtonDownTime == (Time) 0) {

		delta = screen->multiClickTime + 1;
	    } else if (event->xbutton.time > lastButtonDownTime) {

		delta = (int) (event->xbutton.time - lastButtonDownTime);
	    } else {

		delta = (int) ((((Time) ~ 0) - lastButtonDownTime) + event->xbutton.time);
	    }
	    if (delta > screen->multiClickTime)
		goto finish;
	}
	line = (event->xbutton.y - screen->border) / FontHeight(screen);
	if (!rowOnCurrentLine(screen, line, &ldelta))
	    goto finish;

	col = (event->xbutton.x - OriginX(screen) + (FontWidth(screen) - 1)
	       / 2)
	    / FontWidth(screen) - screen->cur_col + ldelta * MaxCols(screen);
	if (col == 0)
	    goto finish;
	Line[0] = ANSI_ESC;

	Line[1] = 'O';
	Line[2] = CharOf(col > 0 ? 'C' : 'D');
	if (col < 0)
	    col = -col;
	while (col--)
	    v_write(screen->respond, Line, 3);
      finish:
	if (event->type == ButtonRelease)
	    do_select_end(xw, event, params, num_params, False);
    }
}
