try_match(num *t, num *r, match *m) {
	if(t->value == r->value) {
		if(m->root == NULL) {
			m->root = t;
		}

		m->success();
		return match::singleton(m);
	}

	return m->failure();
}
