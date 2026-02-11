do_rehash (MonoValueHashTable *hash)
{
	int i;
	int old_size;
	Slot *old_table;

	old_size = hash->table_size;
	old_table = hash->table;

	mono_value_hash_table_set_shift_from_size (hash, hash->in_use * 2);


	hash->table = g_new0 (Slot, hash->table_size);

	for (i = 0; i < old_size; i++){
		Slot *s = &old_table [i];
		Slot *new_s;
		guint hash_val;
		guint step = 0;
		gpointer s_value, s_key;

		if (IS_EMPTY (s) || IS_TOMBSTONE (s))
			continue;

		s_value = GET_VALUE (s);
		s_key = hash->key_extract_func (s_value);
		hash_val = HASH (hash, s_key) & hash->table_mask;
		new_s = &hash->table [hash_val];

		while (!IS_EMPTY (new_s)) {
			step++;
			hash_val += step;
			hash_val &= hash->table_mask;
			new_s = &hash->table [hash_val];
		}

		*new_s = *s;
	}
	g_free (old_table);
	hash->n_occupied = hash->in_use;
}
