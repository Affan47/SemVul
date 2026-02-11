do_incl(String *params, Cardinal *no_params)
{
    if (*no_params > 0) {
	if (case_lstrcmp(params[0], "true") == 0 ||
	    case_lstrcmp(params[0], "yes"))
	    ToggleGadgetSet(include_toggle, True);
	else if (case_lstrcmp(params[0], "false") == 0 ||
		 case_lstrcmp(params[0], "no") == 0)
	    ToggleGadgetSet(include_toggle, False);
    }
}
