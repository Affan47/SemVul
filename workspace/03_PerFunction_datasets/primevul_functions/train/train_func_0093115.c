InterpretEvent(XtermWidget xw, XEvent *event)
{
    Bool result = False;

    if (IsBtnEvent(event)) {
	result = InterpretButton(xw, (XButtonEvent *) event);
    } else if (event->type == MotionNotify) {
	unsigned state = event->xmotion.state;
	int button = MotionButton(state);

	if (ShiftOverride(xw, state, button)) {
	    TRACE(("...shift-motion #%d (%d,%d) overrides mouse-protocol\n",
		   button,
		   event->xmotion.y,
		   event->xmotion.x));
	    result = True;
	}
    }
    return result;
}
