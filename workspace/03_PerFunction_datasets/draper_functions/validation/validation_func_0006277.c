CatchButton(EventType t, int b) {
    switch (t) {
	case DownEvent:
	    mask |= downmask;
	    SetButton(down, b);
	    break;
	case UpEvent:
	    mask |= upmask;
	    SetButton(up, b);
	    break;
	case KeyEvent:
	    mask |= keymask;
	    SetButton(down, b);
	    break;
	default:

	    break;
    }
}
