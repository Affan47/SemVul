HandleInsertFormatted(Widget w,
		      XEvent *event,
		      String *params,
		      Cardinal *num_params)
{
    XtermWidget xw;

    TRACE_EVENT("HandleInsertFormatted", event, params, num_params);
    if ((xw = getXtermWidget(w)) != 0 &&
	(*num_params > 1)) {
	doSelectionFormat(xw, w, event, params, num_params, reallyInsertFormatted);
    }
}
