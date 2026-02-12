isDoubleClick3(XtermWidget xw, TScreen *screen, XButtonEvent *event)
{
    int delta;

    if (event->type != ButtonRelease
	|| OverrideButton(event)
	|| event->button != Button3) {
	lastButton3UpTime = 0;
	return 0;
    }

    if (lastButton3DoubleDownTime == (Time) 0) {

	delta = screen->multiClickTime + 1;
    } else if (event->time > lastButton3DoubleDownTime) {

	delta = (int) (event->time - lastButton3DoubleDownTime);
    } else {

	delta = (int) ((((Time) ~ 0) - lastButton3DoubleDownTime) + event->time);
    }
    if (delta <= screen->multiClickTime) {

	CELL cell;


	PointToCELL(screen, event->y, event->x, &cell);
	if (isSameCELL(&cell, &lastButton3)) {
	    lastButton3DoubleDownTime = 0;
	    return 1;
	}
    }

    lastButton3UpTime = event->time;
    PointToCELL(screen, event->y, event->x, &lastButton3);
    return 0;
}
