action_popup_find_group(Widget w, XEvent *event,
			     String *params, Cardinal *no_params)
{
    if (global.busy)
	return;

    popup_find_group();
}
