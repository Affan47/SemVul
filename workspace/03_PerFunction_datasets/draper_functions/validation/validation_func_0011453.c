ResetCanvasWidget(ocw, mask, value)
OffTheSpotConversionWidget ocw;
unsigned long mask;
ConversionAttributes *value;
{
    Arg arg[10];
    Cardinal i = 0;
    Boolean redraw = False;

    if (mask & CAClientArea) {
	XtSetArg(arg[i], XtNx, value->clientarea.x); i++;
	XtSetArg(arg[i], XtNy, value->clientarea.y); i++;
	XtSetArg(arg[i], XtNwidth, value->clientarea.width); i++;
	XtSetArg(arg[i], XtNheight, value->clientarea.height); i++;
	redraw = True;
    }

    if (mask & CAColormap) {
	XtSetArg(arg[i], XtNcolormap, value->colormap); i++;
	redraw = True;
    }
    if (mask & CAColor) {
	XtSetArg(arg[i], XtNbackground, value->background); i++;
	redraw = True;
    }
    if (mask & CACursor) {
	XtSetArg(arg[i], XtNcursor, value->cursor); i++;
    }

    XtSetValues(ocw->offthespot.canvaswidget, arg, i);

    return redraw;
}
