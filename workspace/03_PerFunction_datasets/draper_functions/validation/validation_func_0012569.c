aging_lookup_revitalise(aging_table_t *ag, const void *key)
{
	struct aging_value *aval;

	aging_check(ag);

	aval = hikset_lookup(ag->table, key);

	if (aval != NULL) {
		aval->last_insert = tm_time();
		aging_moveto_tail(ag, aval);
	}

	return NULL == aval ? NULL : aval->value;
}
