isClick1_clean(XtermWidget xw, XButtonEvent *event)
{
    TScreen *screen = TScreenOf(xw);
    int delta;


    if (OverrideButton(event)
	|| (okSendMousePos(xw) != MOUSE_OFF)
	|| ExtendingSelection)
	return 0;

    if (event->type != ButtonRelease)
	return 0;

    if (lastButtonDownTime == (Time) 0) {

	delta = screen->multiClickTime + 1;
    } else if (event->time > lastButtonDownTime) {

	delta = (int) (event->time - lastButtonDownTime);
    } else {

	delta = (int) ((((Time) ~ 0) - lastButtonDownTime) + event->time);
    }

    return delta <= screen->multiClickTime;
}
