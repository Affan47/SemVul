eventRow(TScreen *screen, XEvent *event)
{
    return (event->xbutton.y - screen->border) / FontHeight(screen);
}
