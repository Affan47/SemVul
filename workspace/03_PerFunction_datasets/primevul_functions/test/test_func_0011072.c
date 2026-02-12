_nc_init_pair(SCREEN *sp, int pair, int f, int b)
{
    static colorpair_t null_pair;
    colorpair_t result = null_pair;
    colorpair_t previous;
    int maxcolors;

    T((T_CALLED("init_pair(%p,%d,%d,%d)"), (void *) sp, pair, f, b));

    if (!ValidPair(sp, pair))
	returnCode(ERR);

    maxcolors = MaxColors;

    ReservePairs(sp, pair);
    previous = sp->_color_pairs[pair];
#if NCURSES_EXT_FUNCS
    if (sp->_default_color || sp->_assumed_color) {
	bool isDefault = FALSE;
	bool wasDefault = FALSE;
	int default_pairs = sp->_default_pairs;


	if (isDefaultColor(f)) {
	    f = COLOR_DEFAULT;
	    isDefault = TRUE;
	} else if (!OkColorHi(f)) {
	    returnCode(ERR);
	}

	if (isDefaultColor(b)) {
	    b = COLOR_DEFAULT;
	    isDefault = TRUE;
	} else if (!OkColorHi(b)) {
	    returnCode(ERR);
	}


	if (isDefaultColor(FORE_OF(previous))
	    || isDefaultColor(BACK_OF(previous)))
	    wasDefault = TRUE;


	if (isDefault && !wasDefault) {
	    ++default_pairs;
	} else if (wasDefault && !isDefault) {
	    --default_pairs;
	}


	if (pair > (sp->_pair_count + default_pairs)) {
	    returnCode(ERR);
	}
	sp->_default_pairs = default_pairs;
    } else
#endif
    {
	if ((f < 0) || !OkColorHi(f)
	    || (b < 0) || !OkColorHi(b)
	    || (pair < 1)) {
	    returnCode(ERR);
	}
    }


    MakeColorPair(result, f, b);
    if ((FORE_OF(previous) != 0
	 || BACK_OF(previous) != 0)
	&& !isSamePair(previous, result)) {
	_nc_change_pair(sp, pair);
    }

    _nc_reset_color_pair(sp, pair, &result);
    sp->_color_pairs[pair] = result;
    _nc_set_color_pair(sp, pair, cpINIT);

    if (GET_SCREEN_PAIR(sp) == pair)
	SET_SCREEN_PAIR(sp, (int) (~0));

#ifdef USE_TERM_DRIVER
    CallDriver_3(sp, td_initpair, pair, f, b);
#else
    if (initialize_pair && InPalette(f) && InPalette(b)) {
	const color_t *tp = DefaultPalette;

	TR(TRACE_ATTRS,
	   ("initializing pair: pair = %d, fg=(%d,%d,%d), bg=(%d,%d,%d)",
	    (int) pair,
	    (int) tp[f].red, (int) tp[f].green, (int) tp[f].blue,
	    (int) tp[b].red, (int) tp[b].green, (int) tp[b].blue));

	NCURSES_PUTP2("initialize_pair",
		      TIPARM_7(initialize_pair,
			       pair,
			       (int) tp[f].red,
			       (int) tp[f].green,
			       (int) tp[f].blue,
			       (int) tp[b].red,
			       (int) tp[b].green,
			       (int) tp[b].blue));
    }
#endif

    returnCode(OK);
}
