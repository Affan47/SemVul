_qWriteSelectionData(XtermWidget xw, Char *lag, unsigned length)
{
    TScreen *screen = TScreenOf(xw);


    if ((xw->flags & NATIONAL) && (length != 0)) {
	ToNational(xw, lag, &length);
    }
#if OPT_PASTE64
    if (screen->base64_paste) {

	Char *p = lag;
	Char buf[64];
	unsigned x = 0;

	TRACE(("convert to base64 %d:%s\n", length, visibleChars(p, length)));


	if (screen->base64_paste && screen->unparse_len) {
	    unparse_end(xw);
	}
	while (length--) {
	    switch (screen->base64_count) {
	    case 0:
		buf[x++] = CharOf(base64_code[*p >> 2]);
		screen->base64_accu = (unsigned) (*p & 0x3);
		screen->base64_count = 2;
		++p;
		break;
	    case 2:
		buf[x++] = CharOf(base64_code[(screen->base64_accu << 4) +
					      (*p >> 4)]);
		screen->base64_accu = (unsigned) (*p & 0xF);
		screen->base64_count = 4;
		++p;
		break;
	    case 4:
		buf[x++] = CharOf(base64_code[(screen->base64_accu << 2) +
					      (*p >> 6)]);
		buf[x++] = CharOf(base64_code[*p & 0x3F]);
		screen->base64_accu = 0;
		screen->base64_count = 0;
		++p;
		break;
	    }
	    if (x >= 63) {

		screen->base64_pad += x;
		TRACE(("writing base64 interim %s\n", visibleChars(buf, x)));
		tty_vwrite(screen->respond, buf, x);
		x = 0;
	    }
	}
	if (x != 0) {
	    screen->base64_pad += x;
	    TRACE(("writing base64 finish %s\n", visibleChars(buf, x)));
	    tty_vwrite(screen->respond, buf, x);
	}
    } else
#endif
#if OPT_READLINE
    if (SCREEN_FLAG(screen, paste_quotes)) {
	while (length--) {
	    tty_vwrite(screen->respond, (const Char *) "\026", 1);
	    tty_vwrite(screen->respond, lag++, 1);
	}
    } else
#endif
    {
	TRACE(("writing base64 padding %s\n", visibleChars(lag, length)));
	tty_vwrite(screen->respond, lag, length);
    }
}
