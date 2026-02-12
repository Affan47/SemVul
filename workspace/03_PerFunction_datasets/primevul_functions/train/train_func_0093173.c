SelectSet(XtermWidget xw,
	  XEvent *event GCC_UNUSED,
	  String *params,
	  Cardinal num_params)
{
    TScreen *screen = TScreenOf(xw);

    TRACE(("SelectSet\n"));

    if (!isSameCELL(&(screen->startSel), &(screen->endSel))) {
	Cardinal n;
	for (n = 0; n < num_params; ++n) {
	    SaltTextAway(xw,
			 TargetToSelection(screen, params[n]),
			 &(screen->startSel), &(screen->endSel));
	}
	_OwnSelection(xw, params, num_params);
    } else {
	ScrnDisownSelection(xw);
    }
}
