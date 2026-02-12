eventColBetween(TScreen *screen, XEvent *event)
{

    return ((event->xbutton.x - OriginX(screen) + (FontWidth(screen) - 1) / 2)
	    / FontWidth(screen));
}
