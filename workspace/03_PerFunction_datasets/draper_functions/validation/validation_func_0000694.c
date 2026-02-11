Escape_action(Widget w _is_unused, XEvent *event _is_unused, String *params _is_unused,
    Cardinal *num_params _is_unused)
{
	action_debug(Escape_action, event, params, num_params);
	if (!appres.secure && !appres.no_prompt) {
	    	host_cancel_reconnect();
		screen_suspend();
	}
}
