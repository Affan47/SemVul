QueryGeometry(Widget gw,
				      XtWidgetGeometry *intended,
				      XtWidgetGeometry *preferred)
{
    ManagerWidget	w = (ManagerWidget)gw;
    Widget		child = find_child(w);
    Dimension		pref_width = w->manager.pref_width;
    Dimension		pref_height = w->manager.pref_height;
    Dimension		intended_width, intended_height;

    if (intended->request_mode & CWWidth)
	intended_width = intended->width;
    else
	intended_width = w->core.width;

    if (intended->request_mode & CWHeight)
	intended_height = intended->height;
    else
	intended_height = w->core.height;

    if (pref_width == 0 || pref_height == 0) {
	XtWidgetGeometry	child_pref;
	XtGeometryResult	result;

	if (!child)
	    return XtGeometryNo;

	result = XtQueryGeometry(child, NULL, &child_pref);
	if (result == XtGeometryAlmost) {
	    if ((child_pref.request_mode & CWWidth) && pref_width == 0)
		pref_width = child_pref.width;
	    if ((child_pref.request_mode & CWHeight) && pref_height == 0)
		pref_height = child_pref.height;
	}
	if (pref_width == 0)
	    pref_width = child->core.width;
	if (pref_height == 0)
	    pref_height = child->core.height;
    }

    preferred->request_mode = CWWidth | CWHeight;
    preferred->width = pref_width;
    preferred->height = pref_height;

    if (pref_width == w->core.width && pref_height == w->core.height)
	return XtGeometryNo;
    if (pref_width == intended_width && pref_height == intended_height)
	return XtGeometryYes;

    return XtGeometryAlmost;
}
