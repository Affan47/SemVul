HandleKeyboardStartExtend(Widget w,
			  XEvent *event,
			  String *params,
			  Cardinal *num_params)
{
    XtermWidget xw;

    if ((xw = getXtermWidget(w)) != 0) {
	TRACE_EVENT("HandleKeyboardStartExtend", event, params, num_params);
	do_start_extend(xw, event, params, num_params, True);
    }
}
