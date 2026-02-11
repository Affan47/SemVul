stf_parse_fixed_cell (Source_t *src, StfParseOptions_t *parseoptions)
{
	char *res;
	char const *cur;
	int splitval;

	g_return_val_if_fail (src != NULL, NULL);
	g_return_val_if_fail (parseoptions != NULL, NULL);

	cur = src->position;

	if (src->splitpos < my_garray_len (parseoptions->splitpositions))
		splitval = (int) g_array_index (parseoptions->splitpositions, int, src->splitpos);
	else
		splitval = -1;

	while (*cur != 0 && !compare_terminator (cur, parseoptions) && splitval != src->linepos) {
		src->linepos++;
	        cur = g_utf8_next_char (cur);
	}

	res = g_string_chunk_insert_len (src->chunk,
					 src->position,
					 cur - src->position);

	src->position = cur;

	return res;
}
