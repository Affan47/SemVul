HandleSelectEnd(Widget w,
		XEvent *event,
		String *params,
		Cardinal *num_params)
{
    XtermWidget xw;

    if ((xw = getXtermWidget(w)) != 0) {
	TRACE(("HandleSelectEnd\n"));
	do_select_end(xw, event, params, num_params, False);
    }
}
