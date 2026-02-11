find_tag (const char *tag,
          const GByteArray *array,
          gsize start_at,
          gsize *out_pos)
{
	gsize i, taglen;
	gsize len = array->len - start_at;

	g_return_val_if_fail (out_pos != NULL, FALSE);

	taglen = strlen (tag);
	if (len >= taglen) {
		for (i = 0; i < len - taglen + 1; i++) {
			if (memcmp (array->data + start_at + i, tag, taglen) == 0) {
				*out_pos = start_at + i;
				return TRUE;
			}
		}
	}
	return FALSE;
}
