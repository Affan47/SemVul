opdb_find(const char *name)
{
	int i;

	for (i = 0; i < ARRAY_LEN(keys); i++) {
		const struct opdb_key *key = &keys[i];

		if (!strcasecmp(key->name, name))
			return i;
	}

	return -1;
}
