html_tok_get (xml_tok_state * s, char **data)
{
	static int got_a_stored_tag = 0;
	static char stored_tag[4096];
	static int stored_type = t_eof;
	static char opentags[64][64];
	static int level = 0;
	char *rdata;
	int type;

	if (got_a_stored_tag) {
		got_a_stored_tag = 0;
		*data = (char *) &stored_tag;
		return stored_type;
	}

	type = xml_tok_get (s, &rdata);

	switch (type) {
		case t_tag:
			if (level >= 0) {
				if (!strcmp (opentags[level - 1], rdata)) {
					got_a_stored_tag = 1;
					strcpy (stored_tag, rdata);
					stored_type = type;
					return t_closetag;
				}
			}
			strcpy (opentags[level], rdata);
			level++;
			break;
		case t_endtag:
			*data = rdata;
			if (string_is_oneof (rdata, empty_tags)) {
				level--;
				return t_closeemptytag;
			}
			break;
		case t_closeemptytag:
		case t_closetag:
			level--;
			if (strcmp (opentags[level], rdata)) {
				fprintf (stderr, "%s/%s\n", opentags[level], rdata);

				got_a_stored_tag = 1;
				stored_type = t_closetag;
				strcpy (stored_tag, rdata);
				level--;
				return t_closetag;
			}
			break;
		default:
			break;
	}

	*data = rdata;
	return type;
}
