PutAttrChar(NCURSES_SP_DCLx CARG_CH_T ch)
{
    int chlen = 1;
    NCURSES_CH_T my_ch;
#if USE_WIDEC_SUPPORT
    PUTC_DATA;
#endif
    NCURSES_CH_T tilde;
    NCURSES_CH_T attr = CHDEREF(ch);

    TR(TRACE_CHARPUT, ("PutAttrChar(%s) at (%d, %d)",
		       _tracech_t(ch),
		       SP_PARM->_cursrow, SP_PARM->_curscol));
#if USE_WIDEC_SUPPORT


    if (isWidecExt(CHDEREF(ch))) {
	TR(TRACE_CHARPUT, ("...skip"));
	return;
    }


    if ((chlen = _nc_wacs_width(CharOf(CHDEREF(ch)))) <= 0) {
	static const NCURSES_CH_T blank = NewChar(BLANK_TEXT);


	if (is8bits(CharOf(CHDEREF(ch)))
	    && (isprint(CharOf(CHDEREF(ch)))
		|| (SP_PARM->_legacy_coding > 0 && CharOf(CHDEREF(ch)) >= 160)
		|| (SP_PARM->_legacy_coding > 1 && CharOf(CHDEREF(ch)) >= 128)
		|| (AttrOf(attr) & A_ALTCHARSET
		    && ((CharOfD(ch) < ACS_LEN
			 && SP_PARM->_acs_map != 0
			 && SP_PARM->_acs_map[CharOfD(ch)] != 0)
			|| (CharOfD(ch) >= 128))))) {
	    ;
	} else {
	    ch = CHREF(blank);
	    TR(TRACE_CHARPUT, ("forced to blank"));
	}
	chlen = 1;
    }
#endif

    if ((AttrOf(attr) & A_ALTCHARSET)
	&& SP_PARM->_acs_map != 0
	&& ((CharOfD(ch) < ACS_LEN)
#if !NCURSES_WCWIDTH_GRAPHICS
	    || is_wacs_value(CharOfD(ch))
#endif
	)) {
	int c8;
	my_ch = CHDEREF(ch);
	c8 = CharOf(my_ch);
#if USE_WIDEC_SUPPORT


	if (SP_PARM->_screen_unicode
	    && _nc_wacs[CharOf(my_ch)].chars[0]) {
	    if (SP_PARM->_screen_acs_map[CharOf(my_ch)]) {
		if (SP_PARM->_screen_acs_fix) {
		    RemAttr(attr, A_ALTCHARSET);
		    my_ch = _nc_wacs[CharOf(my_ch)];
		}
	    } else {
		RemAttr(attr, A_ALTCHARSET);
		my_ch = _nc_wacs[CharOf(my_ch)];
	    }
#if !NCURSES_WCWIDTH_GRAPHICS
	    if (!(AttrOf(attr) & A_ALTCHARSET)) {
		chlen = 1;
	    }
#endif
	} else
#endif
	if (!SP_PARM->_screen_acs_map[c8]) {


	    chtype temp = UChar(SP_PARM->_acs_map[c8]);
	    if (temp) {
		RemAttr(attr, A_ALTCHARSET);
		SetChar(my_ch, temp, AttrOf(attr));
	    }
	}


	if (AttrOf(attr) & A_ALTCHARSET) {
	    int j = CharOfD(ch);
	    chtype temp = UChar(SP_PARM->_acs_map[j]);

	    if (temp != 0) {
		SetChar(my_ch, temp, AttrOf(attr));
	    } else {
		my_ch = CHDEREF(ch);
		RemAttr(attr, A_ALTCHARSET);
	    }
	}
	ch = CHREF(my_ch);
    }
#if USE_WIDEC_SUPPORT && !NCURSES_WCWIDTH_GRAPHICS
    else if (chlen > 1 && is_wacs_value(CharOfD(ch))) {
	chlen = 1;
    }
#endif
    if (tilde_glitch && (CharOfD(ch) == L('~'))) {
	SetChar(tilde, L('`'), AttrOf(attr));
	ch = CHREF(tilde);
    }

    UpdateAttrs(SP_PARM, attr);
    PUTC(CHDEREF(ch));
#if !USE_WIDEC_SUPPORT
    COUNT_OUTCHARS(1);
#endif
    SP_PARM->_curscol += chlen;
    if (char_padding) {
	NCURSES_PUTP2("char_padding", char_padding);
    }
}
