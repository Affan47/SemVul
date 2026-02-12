R_API int r_egg_include(REgg *egg, const char *file, int format) {
	int sz;
	const ut8 *foo = (const ut8 *)r_file_slurp (file, &sz);
	if (!foo) {
		return 0;
	}

	switch (format) {
	case 'r':
		r_egg_raw (egg, foo, sz);
		break;
	case 'a':
		r_buf_append_bytes (egg->buf, foo, sz);
		break;
	default:
		r_buf_append_bytes (egg->src, foo, sz);
	}
	free ((void *)foo);
	return 1;
}
