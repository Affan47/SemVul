ShiftOverride(XtermWidget xw, unsigned state, int button)
{
    unsigned check = (state & OurModifiers(xw));
    Boolean result = False;

    if (check & ShiftMask) {
	if (xw->keyboard.shift_escape == ssFalse ||
	    xw->keyboard.shift_escape == ssNever) {
	    result = True;
	} else if (xw->keyboard.shift_escape == ssTrue) {


	    if (button > 0 && button <= MaxMouseBtn) {
		if (xw->keyboard.shift_buttons & (1U << (button - 1))) {
		    result = True;
		}
	    } else {
		result = True;
	    }
	}
    }
    TRACE2(("ShiftOverride ( %#x -> %#x ) %d\n", state, check, result));
    return result;
}
