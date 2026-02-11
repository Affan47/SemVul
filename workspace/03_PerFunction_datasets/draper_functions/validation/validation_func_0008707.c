hash_add (HASH * table, void *key, void *data)
{
    HASHENT *he = CALLOC (1, sizeof (HASHENT));
    unsigned int sum;

    if (!he)
	return -1;
    ASSERT (key != 0);
    ASSERT (data != 0);
    ASSERT (table != 0);
    he->key = key;
    he->data = data;
    sum = table->hash_key (key) % table->numbuckets;
    he->next = table->bucket[sum];
    table->bucket[sum] = he;
    table->dbsize++;
    return 0;
}
