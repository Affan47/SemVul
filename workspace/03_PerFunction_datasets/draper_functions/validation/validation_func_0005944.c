do_rehash (GHashTable *hash)
{
	int current_size, i;
	Slot **table;


	hash->last_rehash = hash->table_size;
	current_size = hash->table_size;
	hash->table_size = g_spaced_primes_closest (hash->in_use);

	table = hash->table;
	hash->table = g_new0 (Slot *, hash->table_size);

	for (i = 0; i < current_size; i++){
		Slot *s, *next;

		for (s = table [i]; s != NULL; s = next){
			guint hashcode = ((*hash->hash_func) (s->key)) % hash->table_size;
			next = s->next;

			s->next = hash->table [hashcode];
			hash->table [hashcode] = s;
		}
	}
	g_free (table);
}
