Realize(w, maskp, attr)
Widget w;
XtValueMask *maskp;
XSetWindowAttributes *attr;
{
    CanvasShellWidget csw = (CanvasShellWidget)w;

    if (csw->canvasshell.cursor != None) {
	*maskp |= CWCursor;
	attr->cursor = csw->canvasshell.cursor;
    }
    *maskp |= CWBitGravity;
    attr->bit_gravity = NorthWestGravity;
    (*canvasShellWidgetClass->core_class.superclass->core_class.realize)(w, maskp, attr);
}
