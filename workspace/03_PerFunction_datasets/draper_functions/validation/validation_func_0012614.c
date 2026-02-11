DAOpenDisplay(char *display, int argc, char **argv)
{

    DADisplay = XOpenDisplay(display);
    if (!DADisplay) {
	printf("%s: could not open display %s!\n", progName,
		XDisplayName(display));
	exit(EXIT_FAILURE);
    }

    DADepth	= DefaultDepth(DADisplay, DefaultScreen(DADisplay));
    DAVisual	= DefaultVisual(DADisplay, DefaultScreen(DADisplay));
    DAGC	= DefaultGC(DADisplay, DefaultScreen(DADisplay));
}
