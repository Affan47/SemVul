Resize(w)
Widget w;
{
    ConversionControlWidget ccw = (ConversionControlWidget)w;
    Widget child;
    int i;

    TRACE(("ConversionControl:Resize()\n"));


    for (i = 0; i < ccw->composite.num_children; i++) {
	child = ccw->composite.children[i];
	if (XtIsWidget(child) && child->core.managed) {
	    XtResizeWidget(child, ccw->core.width, ccw->core.height,
			   child->core.border_width);
	}
    }
}
