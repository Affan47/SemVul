dump_tags() {
	PSEditText *t;
	int p, ret = 0;

	for (p = 0; p < max_pages; p++) {
		t = get_text(p);
		while (t) {
			if (t->get_tag()) {
				printf("%s=%s\n", t->get_tag(), t->get_text());
				ret++;
			}
			t = t->get_next();
		}
	}

	return ret;
}
