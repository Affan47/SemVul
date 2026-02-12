input_parse(struct input_ctx *ictx, u_char *buf, size_t len)
{
	struct screen_write_ctx		*sctx = &ictx->ctx;
	const struct input_state	*state = NULL;
	const struct input_transition	*itr = NULL;
	size_t				 off = 0;


	while (off < len) {
		ictx->ch = buf[off++];


		if (ictx->state != state ||
		    itr == NULL ||
		    ictx->ch < itr->first ||
		    ictx->ch > itr->last) {
			itr = ictx->state->transitions;
			while (itr->first != -1 && itr->last != -1) {
				if (ictx->ch >= itr->first &&
				    ictx->ch <= itr->last)
					break;
				itr++;
			}
			if (itr->first == -1 || itr->last == -1) {

				fatalx("no transition from state");
			}
		}
		state = ictx->state;


		if (itr->handler != input_print)
			screen_write_collect_end(sctx);


		if (itr->handler != NULL && itr->handler(ictx) != 0)
			continue;


		if (itr->state != NULL)
			input_set_state(ictx, itr);


		if (ictx->state != &input_state_ground)
			evbuffer_add(ictx->since_ground, &ictx->ch, 1);
	}
}
