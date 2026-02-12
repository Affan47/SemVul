EditorButton(XtermWidget xw, XButtonEvent *event)
{
    TScreen *screen = TScreenOf(xw);
    int pty = screen->respond;
    int mouse_limit = MouseLimit(screen);
    Char line[32];
    Char final = 'M';
    int row, col;
    int button;
    unsigned count = 0;
    Boolean changed = True;


    button = (int) (event->button - 1);
    if (button >= 3)
	button++;


    if (screen->send_mouse_pos == X10_MOUSE) {
	if (button > 3)
	    return;
    } else if (screen->extend_coords == SET_SGR_EXT_MODE_MOUSE
	       || screen->extend_coords == SET_URXVT_EXT_MODE_MOUSE
	       || screen->extend_coords == SET_PIXEL_POSITION_MOUSE) {
	if (button > 15) {
	    return;
	}
    } else {
	if (button > 11) {
	    return;
	}
    }

    if (screen->extend_coords == SET_PIXEL_POSITION_MOUSE) {
	row = event->y - OriginY(screen);
	col = event->x - OriginX(screen);
    } else {

	row = (event->y - screen->border) / FontHeight(screen);
	col = (event->x - OriginX(screen)) / FontWidth(screen);


	if (row < 0)
	    row = 0;
	else if (row > screen->max_row)
	    row = screen->max_row;

	if (col < 0)
	    col = 0;
	else if (col > screen->max_col)
	    col = screen->max_col;

	if (mouse_limit > 0) {

	    if (row > mouse_limit)
		row = mouse_limit;
	    if (col > mouse_limit)
		col = mouse_limit;
	}
    }


    if (screen->control_eight_bits) {
	line[count++] = ANSI_CSI;
    } else {
	line[count++] = ANSI_ESC;
	line[count++] = '[';
    }
    switch (screen->extend_coords) {
    case 0:
    case SET_EXT_MODE_MOUSE:
#if OPT_SCO_FUNC_KEYS
	if (xw->keyboard.type == keyboardIsSCO) {


	    line[count++] = '>';
	}
#endif
	line[count++] = final;
	break;
    case SET_SGR_EXT_MODE_MOUSE:
    case SET_PIXEL_POSITION_MOUSE:
	line[count++] = '<';
	break;
    }


    if (okSendMousePos(xw) == X10_MOUSE) {
	count = EMIT_BUTTON(button);
    } else {

	switch (event->type) {
	case ButtonPress:
	    screen->mouse_button |= ButtonBit(button);
	    count = EMIT_BUTTON(button);
	    break;
	case ButtonRelease:


	    screen->mouse_button &= ~ButtonBit(button);
	    if (button < 3 || button > 5) {
		switch (screen->extend_coords) {
		case SET_SGR_EXT_MODE_MOUSE:
		case SET_PIXEL_POSITION_MOUSE:
		    final = 'm';
		    break;
		default:
		    button = -1;
		    break;
		}
	    }
	    count = EMIT_BUTTON(button);
	    break;
	case MotionNotify:


	    if ((row == screen->mouse_row)
		&& (col == screen->mouse_col)) {
		changed = False;
	    } else {
		count = EMIT_BUTTON(FirstBitN(screen->mouse_button));
	    }
	    break;
	default:
	    changed = False;
	    break;
	}
    }

    if (changed) {
	screen->mouse_row = row;
	screen->mouse_col = col;

	TRACE(("mouse at %d,%d button+mask = %#x\n", row, col, line[count - 1]));


	count = EmitMousePositionSeparator(screen, line, count);
	count = EmitMousePosition(screen, line, count, col);
	count = EmitMousePositionSeparator(screen, line, count);
	count = EmitMousePosition(screen, line, count, row);

	switch (screen->extend_coords) {
	case SET_SGR_EXT_MODE_MOUSE:
	case SET_URXVT_EXT_MODE_MOUSE:
	case SET_PIXEL_POSITION_MOUSE:
	    line[count++] = final;
	    break;
	}


	TRACE(("EditorButton -> %s\n", visibleChars(line, count)));
	v_write(pty, line, count);
    }
    return;
}
