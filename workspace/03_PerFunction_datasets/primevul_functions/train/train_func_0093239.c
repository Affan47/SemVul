CheckSecondPress3(XtermWidget xw, TScreen *screen, XEvent *event)
{
    int delta;

    if (event->type != ButtonPress
	|| OverrideEvent(event)
	|| event->xbutton.button != Button3) {
	lastButton3DoubleDownTime = 0;
	return 0;
    }

    if (lastButton3UpTime == (Time) 0) {

	delta = screen->multiClickTime + 1;
    } else if (event->xbutton.time > lastButton3UpTime) {

	delta = (int) (event->xbutton.time - lastButton3UpTime);
    } else {

	delta = (int) ((((Time) ~ 0) - lastButton3UpTime) + event->xbutton.time);
    }
    if (delta <= screen->multiClickTime) {
	CELL cell;

	PointToCELL(screen, event->xbutton.y, event->xbutton.x, &cell);
	if (isSameCELL(&cell, &lastButton3)) {

	    lastButton3DoubleDownTime = event->xbutton.time;
	    PointToCELL(screen, event->xbutton.y, event->xbutton.x, &lastButton3);
	    return 1;
	}
	lastButton3UpTime = 0;
    }

    lastButton3DoubleDownTime = 0;
    return 0;
}
