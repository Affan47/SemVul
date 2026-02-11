conference_find_by_uids(session_t *s, const char *from, const char **recipients, int count, int quiet)
{
	int i;
	struct conference *c;

	for (c = conferences; c; c = c->next) {
		int matched = 0;

		for (i = 0; i < count; i++)
			if (conference_participant(c, recipients[i]))
				matched++;

		if (conference_participant(c, from))
			matched++;

		debug_function("// conference_find_by_uids(): from=%s, rcpt count=%d, matched=%d, list_count(c->recipients)=%d\n", from, count, matched, LIST_COUNT2(c->recipients));

		if (matched == LIST_COUNT2(c->recipients) && matched <= (!xstrcasecmp(from, s->uid) ? count : count + 1)) {
			string_t new = string_init(NULL);
			int comma = 0;

			if (xstrcasecmp(from, s->uid) && !conference_participant(c, from)) {
				list_add(&c->recipients, xmemdup(&from, sizeof(from)));

				comma++;
				string_append(new, format_user(s, from));
			}

			for (i = 0; i < count; i++) {
				if (xstrcasecmp(recipients[i], s->uid) && !conference_participant(c, recipients[i])) {
					list_add(&c->recipients, xmemdup(&recipients[i], sizeof(recipients[0])));

					if (comma++)
						string_append(new, ", ");
					string_append(new, format_user(s, recipients[i]));
				}
			}

			if (xstrcmp(new->str, "") && !c->ignore)
				printq("conferences_joined", new->str, c->name);
			string_free(new, 1);

			debug("// conference_find_by_uins(): matching %s\n", c->name);

			return c;
		}
	}

	return NULL;
}
