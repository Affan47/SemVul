EvalSelectUnit(XtermWidget xw,
	       Time buttonDownTime,
	       SelectUnit defaultUnit,
	       unsigned int button)
{
    TScreen *screen = TScreenOf(xw);
    SelectUnit result;
    int delta;

    if (button != screen->lastButton) {
	delta = screen->multiClickTime + 1;
    } else if (screen->lastButtonUpTime == (Time) 0) {

	delta = screen->multiClickTime + 1;
    } else if (buttonDownTime > screen->lastButtonUpTime) {

	delta = (int) (buttonDownTime - screen->lastButtonUpTime);
    } else {

	delta = (int) ((((Time) ~ 0) - screen->lastButtonUpTime) + buttonDownTime);
    }

    if (delta > screen->multiClickTime) {
	screen->numberOfClicks = 1;
	result = defaultUnit;
    } else {
	result = screen->selectMap[screen->numberOfClicks % screen->maxClicks];
	screen->numberOfClicks += 1;
    }
    TRACE(("EvalSelectUnit(%d) = %d\n", screen->numberOfClicks, result));
    return result;
}
