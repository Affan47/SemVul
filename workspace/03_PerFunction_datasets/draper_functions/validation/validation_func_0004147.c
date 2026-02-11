scgi_extensions_free(scgi_exts *f) {
	size_t i;

	if (!f) return;

	for (i = 0; i < f->used; i++) {
		scgi_extension *fe;
		size_t j;

		fe = f->exts[i];

		for (j = 0; j < fe->used; j++) {
			scgi_extension_host *h;

			h = fe->hosts[j];

			scgi_host_free(h);
		}

		buffer_free(fe->key);
		free(fe->hosts);

		free(fe);
	}

	free(f->exts);

	free(f);
}
