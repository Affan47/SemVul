Realize(gw, valueMask, attr)
XSetWindowAttributes *attr;
XtValueMask *valueMask;
Widget gw;
{
	CanvasWidget w = (CanvasWidget) gw;


	if ((attr->cursor = w->canvas.idle_cursor) != None)
		*valueMask |= CWCursor;


	XtCreateWindow(gw, InputOutput, (Visual *) CopyFromParent,
		       *valueMask, attr);


	canvasClearPicture(w);
}
