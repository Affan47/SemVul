_closure_term(struct parse_sp *ps)
{
	struct rx_node *l, *n;

	if (!(l = _term(ps)))
		return NULL;

	for (;;) {
		switch (ps->type) {
		case '*':
			n = _node(ps->mem, STAR, l, NULL);
			break;

		case '+':
			n = _node(ps->mem, PLUS, l, NULL);
			break;

		case '?':
			n = _node(ps->mem, QUEST, l, NULL);
			break;

		default:
			return l;
		}

		if (!n) {
			stack;
			return NULL;
		}

		_rx_get_token(ps);
		l = n;
	}

	return n;
}
