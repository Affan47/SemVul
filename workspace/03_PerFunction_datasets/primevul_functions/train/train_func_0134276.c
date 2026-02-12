R_API void r_egg_reset(REgg *egg) {
	r_egg_lang_include_init (egg);

	r_buf_free (egg->src);
	r_buf_free (egg->buf);
	r_buf_free (egg->bin);
	egg->src = r_buf_new ();
	egg->buf = r_buf_new ();
	egg->bin = r_buf_new ();
	r_list_purge (egg->patches);
}
