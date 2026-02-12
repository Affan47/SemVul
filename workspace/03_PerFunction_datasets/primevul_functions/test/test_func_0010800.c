_nc_mouse_parse(SCREEN *sp, int runcount)

{
    MEVENT *eventp = sp->_mouse_eventp;
    MEVENT *next, *ep;
    MEVENT *first_valid = NULL;
    MEVENT *first_invalid = NULL;
    int n;
    int b;
    bool merge;
    bool endLoop;

    TR(MY_TRACE, ("_nc_mouse_parse(%d) called", runcount));


    ep = eventp;
    for (n = runcount; n < EV_MAX; n++) {
	Invalidate(ep);
	ep = NEXT(ep);
    }

#ifdef TRACE
    if (USE_TRACEF(TRACE_IEVENT)) {
	_trace_slot(sp, "before mouse press/release merge:");
	_tracef("_nc_mouse_parse: run starts at %ld, ends at %ld, count %d",
		RunParams(sp, eventp, ep),
		runcount);
	_nc_unlock_global(tracef);
    }
#endif


    endLoop = FALSE;
    while (!endLoop) {
	next = NEXT(ep);
	if (next == eventp) {

	    endLoop = TRUE;
	} else {

#define MASK_CHANGED(x) (!(ep->bstate & MASK_PRESS(x)) \
		      == !(next->bstate & MASK_RELEASE(x)))

	    if (ValidEvent(ep) && ValidEvent(next)
		&& ep->x == next->x && ep->y == next->y
		&& (ep->bstate & BUTTON_PRESSED)
		&& (!(next->bstate & BUTTON_PRESSED))) {
		bool changed = TRUE;

		for (b = 1; b <= MAX_BUTTONS; ++b) {
		    if (!MASK_CHANGED(b)) {
			changed = FALSE;
			break;
		    }
		}

		if (changed) {
		    merge = FALSE;
		    for (b = 1; b <= MAX_BUTTONS; ++b) {
			if ((sp->_mouse_mask & MASK_CLICK(b))
			    && (ep->bstate & MASK_PRESS(b))) {
			    next->bstate &= ~MASK_RELEASE(b);
			    next->bstate |= MASK_CLICK(b);
			    merge = TRUE;
			}
		    }
		    if (merge) {
			Invalidate(ep);
		    }
		}
	    }
	}


	if (!ValidEvent(ep)) {
	    if ((first_valid != NULL) && (first_invalid == NULL)) {
		first_invalid = ep;
	    }
	} else {
	    if (first_valid == NULL) {
		first_valid = ep;
	    } else if (first_invalid != NULL) {
		*first_invalid = *ep;
		Invalidate(ep);
		first_invalid = NEXT(first_invalid);
	    }
	}

	ep = next;
    }

    if (first_invalid != NULL) {
	eventp = first_invalid;
    }
#ifdef TRACE
    if (USE_TRACEF(TRACE_IEVENT)) {
	_trace_slot(sp, "before mouse click merge:");
	if (first_valid == NULL) {
	    _tracef("_nc_mouse_parse: no valid event");
	} else {
	    _tracef("_nc_mouse_parse: run starts at %ld, ends at %ld, count %d",
		    RunParams(sp, eventp, first_valid),
		    runcount);
	    _nc_unlock_global(tracef);
	}
    }
#endif


    first_invalid = NULL;
    endLoop = (first_valid == NULL);
    ep = first_valid;
    while (!endLoop) {
	next = NEXT(ep);

	if (next == eventp) {

	    endLoop = TRUE;
	} else if (!ValidEvent(next)) {
	    continue;
	} else {

	    if ((ep->bstate & BUTTON_CLICKED)
		&& (next->bstate & BUTTON_CLICKED)) {
		merge = FALSE;
		for (b = 1; b <= MAX_BUTTONS; ++b) {
		    if ((sp->_mouse_mask & MASK_DOUBLE_CLICK(b))
			&& (ep->bstate & MASK_CLICK(b))
			&& (next->bstate & MASK_CLICK(b))) {
			next->bstate &= ~MASK_CLICK(b);
			next->bstate |= MASK_DOUBLE_CLICK(b);
			merge = TRUE;
		    }
		}
		if (merge) {
		    Invalidate(ep);
		}
	    }


	    if ((ep->bstate & BUTTON_DOUBLE_CLICKED)
		&& (next->bstate & BUTTON_CLICKED)) {
		merge = FALSE;
		for (b = 1; b <= MAX_BUTTONS; ++b) {
		    if ((sp->_mouse_mask & MASK_TRIPLE_CLICK(b))
			&& (ep->bstate & MASK_DOUBLE_CLICK(b))
			&& (next->bstate & MASK_CLICK(b))) {
			next->bstate &= ~MASK_CLICK(b);
			next->bstate |= MASK_TRIPLE_CLICK(b);
			merge = TRUE;
		    }
		}
		if (merge) {
		    Invalidate(ep);
		}
	    }
	}


	if (!(ep->bstate & sp->_mouse_mask2)) {
	    Invalidate(ep);
	}


	if (!ValidEvent(ep)) {
	    if (ep == first_valid) {
		first_valid = next;
	    } else if (first_invalid == NULL) {
		first_invalid = ep;
	    }
	} else if (first_invalid != NULL) {
	    *first_invalid = *ep;
	    Invalidate(ep);
	    first_invalid = NEXT(first_invalid);
	}

	ep = next;
    }

    if (first_invalid == NULL) {
	first_invalid = eventp;
    }
    sp->_mouse_eventp = first_invalid;

#ifdef TRACE
    if (first_valid != NULL) {
	if (USE_TRACEF(TRACE_IEVENT)) {
	    _trace_slot(sp, "after mouse event queue compaction:");
	    _tracef("_nc_mouse_parse: run starts at %ld, ends at %ld, count %d",
		    RunParams(sp, first_invalid, first_valid),
		    runcount);
	    _nc_unlock_global(tracef);
	}
	for (ep = first_valid; ep != first_invalid; ep = NEXT(ep)) {
	    if (ValidEvent(ep))
		TR(MY_TRACE,
		   ("_nc_mouse_parse: returning composite mouse event %s at slot %ld",
		    _nc_tracemouse(sp, ep),
		    (long) IndexEV(sp, ep)));
	}
    }
#endif


    return ValidEvent(PREV(first_invalid));
}
