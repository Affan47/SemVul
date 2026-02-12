decode_X10_bstate(SCREEN *sp, MEVENT * eventp, unsigned intro)
{
    bool result;
    int button = 0;
    int wheel = (intro & 96) == 96;

    eventp->bstate = 0;

    if (intro >= 96) {
	if (intro >= 160) {
	    button = (int) (intro - 152);
	} else if (intro >= 96) {
	    button = (int) (intro - 92);
	}
    } else {
	button = (intro & 3);
    }

    if (button > MAX_BUTTONS) {
	eventp->bstate = REPORT_MOUSE_POSITION;
    } else if (!handle_wheel(sp, eventp, (int) intro, wheel)) {


	if (sp->_mouse_bstate & BUTTON_PRESSED) {
	    int b;

	    eventp->bstate = BUTTON_RELEASED;
	    for (b = 1; b <= MAX_BUTTONS; ++b) {
		if (!(sp->_mouse_bstate & MASK_PRESS(b)))
		    eventp->bstate &= ~MASK_RELEASE(b);
	    }
	    sp->_mouse_bstate = 0;
	} else {


	    eventp->bstate = REPORT_MOUSE_POSITION;
	}
    }

    if (intro & 4) {
	eventp->bstate |= BUTTON_SHIFT;
    }
    if (intro & 8) {
	eventp->bstate |= BUTTON_ALT;
    }
    if (intro & 16) {
	eventp->bstate |= BUTTON_CTRL;
    }
    result = (eventp->bstate & REPORT_MOUSE_POSITION) ? TRUE : FALSE;
    return result;
}
