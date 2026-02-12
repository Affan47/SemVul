_WriteSelectionData(XtermWidget xw, Char *line, size_t length)
{


#if OPT_PASTE64
    TScreen *screen = TScreenOf(xw);
#endif
    Char *lag, *end;


#ifdef VMS
    tt_pasting = True;
#endif

    end = &line[length];
    lag = line;

#if OPT_PASTE64
    if (screen->base64_paste) {
	_qWriteSelectionData(xw, lag, (unsigned) (end - lag));
	base64_flush(screen);
    } else
#endif
    {
	if (!SCREEN_FLAG(screen, paste_literal_nl)) {
	    Char *cp;
	    for (cp = line; cp != end; cp++) {
		if (*cp == '\n') {
		    *cp = '\r';
		    _qWriteSelectionData(xw, lag, (unsigned) (cp - lag + 1));
		    lag = cp + 1;
		}
	    }
	}

	if (lag != end) {
	    _qWriteSelectionData(xw, lag, (unsigned) (end - lag));
	}
    }
#ifdef VMS
    tt_pasting = False;
    tt_start_read();
#endif
}
