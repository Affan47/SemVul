hash_table_contains(const hash_table_t *ht, const void *key)
{
	bool ret;

	hash_table_check(ht);
	ht_synchronize(ht);

	ret = NULL != hash_table_find(ht, key, NULL);
	ht_return(ht, ret);
}
