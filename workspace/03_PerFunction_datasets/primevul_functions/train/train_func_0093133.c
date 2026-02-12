InitLocatorFilter(XtermWidget xw)
{
    ANSI reply;
    TScreen *screen = TScreenOf(xw);
    Window root, child;
    int rx, ry, x, y;
    unsigned int mask;
    int row = 0, col = 0;
    Bool oor = 0;
    Bool ret;

    ret = XQueryPointer(screen->display, VWindow(screen),
			&root, &child, &rx, &ry, &x, &y, &mask);
    if (ret) {
	LocatorCoords(row, col, x, y, oor);
    }
    if (ret == False || oor) {


	if (screen->loc_filter_top != LOC_FILTER_POS ||
	    screen->loc_filter_left != LOC_FILTER_POS ||
	    screen->loc_filter_bottom != LOC_FILTER_POS ||
	    screen->loc_filter_right != LOC_FILTER_POS) {


	    memset(&reply, 0, sizeof(reply));
	    reply.a_type = ANSI_CSI;
	    reply.a_nparam = 1;
	    reply.a_param[0] = 0;
	    reply.a_inters = '&';
	    reply.a_final = 'w';
	    unparseseq(xw, &reply);

	    if (screen->locator_reset) {
		MotionOff(screen, xw);
		screen->send_mouse_pos = MOUSE_OFF;
	    }
	} else {


	    screen->loc_filter = True;
	    MotionOn(screen, xw);
	}
	return;
    }


    if (screen->locator_pixels) {
	rx = OriginX(screen) * 2 + Width(screen);
	ry = screen->border * 2 + Height(screen);
    } else {
	rx = screen->max_col;
	ry = screen->max_row;
    }

#define	Adjust( coord, def, max )				\
	if( (coord) == LOC_FILTER_POS )	(coord) = (def);	\
	else if ((coord) < 1)		(coord) = 1;		\
	else if ((coord) > (max))	(coord) = (max)

    Adjust(screen->loc_filter_top, row, ry);
    Adjust(screen->loc_filter_left, col, rx);
    Adjust(screen->loc_filter_bottom, row, ry);
    Adjust(screen->loc_filter_right, col, rx);

    if (screen->loc_filter_top > screen->loc_filter_bottom) {
	ry = screen->loc_filter_top;
	screen->loc_filter_top = screen->loc_filter_bottom;
	screen->loc_filter_bottom = ry;
    }

    if (screen->loc_filter_left > screen->loc_filter_right) {
	rx = screen->loc_filter_left;
	screen->loc_filter_left = screen->loc_filter_right;
	screen->loc_filter_right = rx;
    }

    if ((col < screen->loc_filter_left) ||
	(col > screen->loc_filter_right) ||
	(row < screen->loc_filter_top) ||
	(row > screen->loc_filter_bottom)) {
	int state;


	ButtonState(state, mask);

	memset(&reply, 0, sizeof(reply));
	reply.a_type = ANSI_CSI;
	reply.a_nparam = 4;
	reply.a_param[0] = 10;
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
	return;
    }


    screen->loc_filter = True;
    MotionOn(screen, xw);
}
