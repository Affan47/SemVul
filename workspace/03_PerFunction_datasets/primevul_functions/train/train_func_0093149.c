EmitMousePosition(TScreen *screen, Char line[], unsigned count, int value)
{
    int mouse_limit = MouseLimit(screen);


    switch (screen->extend_coords) {
    default:
	if (value == mouse_limit) {
	    line[count++] = CharOf(0);
	} else {
	    line[count++] = CharOf(' ' + value + 1);
	}
	break;
    case SET_EXT_MODE_MOUSE:
	if (value == mouse_limit) {
	    line[count++] = CharOf(0);
	} else if (value < EXT_MOUSE_START) {
	    line[count++] = CharOf(' ' + value + 1);
	} else {
	    value += ' ' + 1;
	    line[count++] = CharOf(0xC0 + (value >> 6));
	    line[count++] = CharOf(0x80 + (value & 0x3F));
	}
	break;
    case SET_SGR_EXT_MODE_MOUSE:
    case SET_URXVT_EXT_MODE_MOUSE:
    case SET_PIXEL_POSITION_MOUSE:
	count += (unsigned) sprintf((char *) line + count, "%d", value + 1);
	break;
    }
    return count;
}
