rndr_header_anchor(struct buf *out, const struct buf *anchor)
{
	static const char *STRIPPED = " -&+$,/:;=?@\"#{}|^~[]`\\*()%.!'";

	const uint8_t *a = anchor->data;
	const size_t size = anchor->size;
	size_t i = 0;
	int stripped = 0, inserted = 0;

	for (; i < size; ++i) {

		if (a[i] == '<') {
			while (i < size && a[i] != '>')
				i++;

		} else if (a[i] == '&') {
			while (i < size && a[i] != ';')
				i++;
		}

		else if (!isascii(a[i]) || strchr(STRIPPED, a[i])) {
			if (inserted && !stripped)
				bufputc(out, '-');

			stripped = 1;
		}
		else {
			bufputc(out, tolower(a[i]));
			stripped = 0;
			inserted++;
		}
	}


	if (stripped && inserted)
		out->size--;


	if (!inserted && anchor->size) {
	        unsigned long hash = 5381;
		for (i = 0; i < size; ++i) {
			hash = ((hash << 5) + hash) + a[i];
		}
		bufprintf(out, "part-%lx", hash);
	}
}
