input_c0_dispatch(struct input_ctx *ictx)
{
	struct screen_write_ctx	*sctx = &ictx->ctx;
	struct window_pane	*wp = ictx->wp;
	struct screen		*s = sctx->s;

	log_debug("%s: '%c", __func__, ictx->ch);

	switch (ictx->ch) {
	case '\000':
		break;
	case '\007':
		wp->window->flags |= WINDOW_BELL;
		break;
	case '\010':
		screen_write_backspace(sctx);
		break;
	case '\011':

		if (s->cx >= screen_size_x(s) - 1)
			break;


		do {
			s->cx++;
			if (bit_test(s->tabs, s->cx))
				break;
		} while (s->cx < screen_size_x(s) - 1);
		break;
	case '\012':
	case '\013':
	case '\014':
		screen_write_linefeed(sctx, 0);
		break;
	case '\015':
		screen_write_carriagereturn(sctx);
		break;
	case '\016':
		ictx->cell.set = 1;
		break;
	case '\017':
		ictx->cell.set = 0;
		break;
	default:
		log_debug("%s: unknown '%c'", __func__, ictx->ch);
		break;
	}

	return (0);
}
