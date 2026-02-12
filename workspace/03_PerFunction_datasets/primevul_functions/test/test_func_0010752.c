TINFO_DOUPDATE(NCURSES_SP_DCL0)
{
    int i;
    int nonempty;
#if USE_TRACE_TIMES
    struct tms before, after;
#endif

    T((T_CALLED("_nc_tinfo:doupdate(%p)"), (void *) SP_PARM));

    _nc_lock_global(update);

    if (SP_PARM == 0) {
	_nc_unlock_global(update);
	returnCode(ERR);
    }
#if !USE_REENTRANT


#define SyncScreens(internal,exported) \
	if (internal == 0) internal = exported; \
	if (internal != exported) exported = internal

    SyncScreens(CurScreen(SP_PARM), curscr);
    SyncScreens(NewScreen(SP_PARM), newscr);
    SyncScreens(StdScreen(SP_PARM), stdscr);
#endif

    if (CurScreen(SP_PARM) == 0
	|| NewScreen(SP_PARM) == 0
	|| StdScreen(SP_PARM) == 0) {
	_nc_unlock_global(update);
	returnCode(ERR);
    }
#ifdef TRACE
    if (USE_TRACEF(TRACE_UPDATE)) {
	if (CurScreen(SP_PARM)->_clear)
	    _tracef("curscr is clear");
	else
	    _tracedump("curscr", CurScreen(SP_PARM));
	_tracedump("newscr", NewScreen(SP_PARM));
	_nc_unlock_global(tracef);
    }
#endif

    _nc_signal_handler(FALSE);

    if (SP_PARM->_fifohold)
	SP_PARM->_fifohold--;

#if USE_SIZECHANGE
    if ((SP_PARM->_endwin == ewSuspend)
	|| _nc_handle_sigwinch(SP_PARM)) {


	_nc_update_screensize(SP_PARM);
    }
#endif

    if (SP_PARM->_endwin == ewSuspend) {

	T(("coming back from shell mode"));
	NCURSES_SP_NAME(reset_prog_mode) (NCURSES_SP_ARG);

	NCURSES_SP_NAME(_nc_mvcur_resume) (NCURSES_SP_ARG);
	NCURSES_SP_NAME(_nc_screen_resume) (NCURSES_SP_ARG);
	SP_PARM->_mouse_resume(SP_PARM);

	SP_PARM->_endwin = ewRunning;
    }
#if USE_TRACE_TIMES

    RESET_OUTCHARS();
    (void) times(&before);
#endif


#if USE_XMC_SUPPORT
    if (magic_cookie_glitch > 0) {
	int j, k;
	attr_t rattr = A_NORMAL;

	for (i = 0; i < screen_lines(SP_PARM); i++) {
	    for (j = 0; j < screen_columns(SP_PARM); j++) {
		bool failed = FALSE;
		NCURSES_CH_T *thisline = NewScreen(SP_PARM)->_line[i].text;
		attr_t thisattr = AttrOf(thisline[j]) & SP_PARM->_xmc_triggers;
		attr_t turnon = thisattr & ~rattr;


		if (turnon == 0) {
		    rattr = thisattr;
		    continue;
		}

		TR(TRACE_ATTRS, ("At (%d, %d): from %s...", i, j, _traceattr(rattr)));
		TR(TRACE_ATTRS, ("...to %s", _traceattr(turnon)));


#define SAFE(scr,a)	(!((a) & (scr)->_xmc_triggers))
		if (ISBLANK(thisline[j]) && SAFE(SP_PARM, turnon)) {
		    RemAttr(thisline[j], turnon);
		    continue;
		}


		for (k = 1; k <= magic_cookie_glitch; k++) {
		    if (j - k < 0
			|| !ISBLANK(thisline[j - k])
			|| !SAFE(SP_PARM, AttrOf(thisline[j - k]))) {
			failed = TRUE;
			TR(TRACE_ATTRS, ("No room at start in %d,%d%s%s",
					 i, j - k,
					 (ISBLANK(thisline[j - k])
					  ? ""
					  : ":nonblank"),
					 (SAFE(SP_PARM, AttrOf(thisline[j - k]))
					  ? ""
					  : ":unsafe")));
			break;
		    }
		}
		if (!failed) {
		    bool end_onscreen = FALSE;
		    int m, n = j;


		    for (m = i; m < screen_lines(SP_PARM); m++) {
			for (; n < screen_columns(SP_PARM); n++) {
			    attr_t testattr =
			    AttrOf(NewScreen(SP_PARM)->_line[m].text[n]);
			    if ((testattr & SP_PARM->_xmc_triggers) == rattr) {
				end_onscreen = TRUE;
				TR(TRACE_ATTRS,
				   ("Range attributed with %s ends at (%d, %d)",
				    _traceattr(turnon), m, n));
				goto foundit;
			    }
			}
			n = 0;
		    }
		    TR(TRACE_ATTRS,
		       ("Range attributed with %s ends offscreen",
			_traceattr(turnon)));
		  foundit:;

		    if (end_onscreen) {
			NCURSES_CH_T *lastline =
			NewScreen(SP_PARM)->_line[m].text;


			while (n >= 0
			       && ISBLANK(lastline[n])
			       && SAFE(SP_PARM, AttrOf(lastline[n]))) {
			    RemAttr(lastline[n--], turnon);
			}


			for (k = 1; k <= magic_cookie_glitch; k++) {
			    if (n + k >= screen_columns(SP_PARM)
				|| !ISBLANK(lastline[n + k])
				|| !SAFE(SP_PARM, AttrOf(lastline[n + k]))) {
				failed = TRUE;
				TR(TRACE_ATTRS,
				   ("No room at end in %d,%d%s%s",
				    i, j - k,
				    (ISBLANK(lastline[n + k])
				     ? ""
				     : ":nonblank"),
				    (SAFE(SP_PARM, AttrOf(lastline[n + k]))
				     ? ""
				     : ":unsafe")));
				break;
			    }
			}
		    }
		}

		if (failed) {
		    int p, q = j;

		    TR(TRACE_ATTRS,
		       ("Clearing %s beginning at (%d, %d)",
			_traceattr(turnon), i, j));


		    for (p = i; p < screen_lines(SP_PARM); p++) {
			for (; q < screen_columns(SP_PARM); q++) {
			    attr_t testattr = AttrOf(newscr->_line[p].text[q]);
			    if ((testattr & SP_PARM->_xmc_triggers) == rattr)
				goto foundend;
			    RemAttr(NewScreen(SP_PARM)->_line[p].text[q], turnon);
			}
			q = 0;
		    }
		  foundend:;
		} else {
		    TR(TRACE_ATTRS,
		       ("Cookie space for %s found before (%d, %d)",
			_traceattr(turnon), i, j));


		    for (k = 1; k <= magic_cookie_glitch; k++)
			AddAttr(thisline[j - k], turnon);
		}

		rattr = thisattr;
	    }
	}

#ifdef TRACE

	if (USE_TRACEF(TRACE_UPDATE)) {
	    _tracef("After magic-cookie check...");
	    _tracedump("newscr", NewScreen(SP_PARM));
	    _nc_unlock_global(tracef);
	}
#endif
    }
#endif

    nonempty = 0;
    if (CurScreen(SP_PARM)->_clear || NewScreen(SP_PARM)->_clear) {
	ClrUpdate(NCURSES_SP_ARG);
	CurScreen(SP_PARM)->_clear = FALSE;
	NewScreen(SP_PARM)->_clear = FALSE;
    } else {
	int changedlines = CHECK_INTERVAL;

	if (check_pending(NCURSES_SP_ARG))
	    goto cleanup;

	nonempty = min(screen_lines(SP_PARM), NewScreen(SP_PARM)->_maxy + 1);

	if (SP_PARM->_scrolling) {
	    NCURSES_SP_NAME(_nc_scroll_optimize) (NCURSES_SP_ARG);
	}

	nonempty = ClrBottom(NCURSES_SP_ARGx nonempty);

	TR(TRACE_UPDATE, ("Transforming lines, nonempty %d", nonempty));
	for (i = 0; i < nonempty; i++) {


	    if (changedlines == CHECK_INTERVAL) {
		if (check_pending(NCURSES_SP_ARG))
		    goto cleanup;
		changedlines = 0;
	    }


	    if (NewScreen(SP_PARM)->_line[i].firstchar != _NOCHANGE
		|| CurScreen(SP_PARM)->_line[i].firstchar != _NOCHANGE) {
		TransformLine(NCURSES_SP_ARGx i);
		changedlines++;
	    }


	    if (i <= NewScreen(SP_PARM)->_maxy) {
		MARK_NOCHANGE(NewScreen(SP_PARM), i);
	    }
	    if (i <= CurScreen(SP_PARM)->_maxy) {
		MARK_NOCHANGE(CurScreen(SP_PARM), i);
	    }
	}
    }


    for (i = nonempty; i <= NewScreen(SP_PARM)->_maxy; i++) {
	MARK_NOCHANGE(NewScreen(SP_PARM), i);
    }
    for (i = nonempty; i <= CurScreen(SP_PARM)->_maxy; i++) {
	MARK_NOCHANGE(CurScreen(SP_PARM), i);
    }

    if (!NewScreen(SP_PARM)->_leaveok) {
	CurScreen(SP_PARM)->_curx = NewScreen(SP_PARM)->_curx;
	CurScreen(SP_PARM)->_cury = NewScreen(SP_PARM)->_cury;

	GoTo(NCURSES_SP_ARGx CurScreen(SP_PARM)->_cury, CurScreen(SP_PARM)->_curx);
    }

  cleanup:


#if USE_XMC_SUPPORT
    if (magic_cookie_glitch != 0)
#endif
	UpdateAttrs(SP_PARM, normal);

    NCURSES_SP_NAME(_nc_flush) (NCURSES_SP_ARG);
    WINDOW_ATTRS(CurScreen(SP_PARM)) = WINDOW_ATTRS(NewScreen(SP_PARM));

#if USE_TRACE_TIMES
    (void) times(&after);
    TR(TRACE_TIMES,
       ("Update cost: %ld chars, %ld clocks system time, %ld clocks user time",
	_nc_outchars,
	(long) (after.tms_stime - before.tms_stime),
	(long) (after.tms_utime - before.tms_utime)));
#endif

    _nc_signal_handler(TRUE);

    _nc_unlock_global(update);
    returnCode(OK);
}
