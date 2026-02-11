dump_hash_table (file, name, table)
     FILE *file;
     const char *name;
     struct hash_table *table;
{
  int i;

  struct expr **flat_table;
  unsigned int *hash_val;
  struct expr *expr;

  flat_table
    = (struct expr **) xcalloc (table->n_elems, sizeof (struct expr *));
  hash_val = (unsigned int *) xmalloc (table->n_elems * sizeof (unsigned int));

  for (i = 0; i < (int) table->size; i++)
    for (expr = table->table[i]; expr != NULL; expr = expr->next_same_hash)
      {
	flat_table[expr->bitmap_index] = expr;
	hash_val[expr->bitmap_index] = i;
      }

  fprintf (file, "%s hash table (%d buckets, %d entries)\n",
	   name, table->size, table->n_elems);

  for (i = 0; i < (int) table->n_elems; i++)
    if (flat_table[i] != 0)
      {
	expr = flat_table[i];
	fprintf (file, "Index %d (hash value %d)\n  ",
		 expr->bitmap_index, hash_val[i]);
	print_rtl (file, expr->expr);
	fprintf (file, "\n");
      }

  fprintf (file, "\n");

  free (flat_table);
  free (hash_val);
}
