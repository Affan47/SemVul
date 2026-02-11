hash_bins_items_arena_size(const hash_table_t *ht, size_t *items_offset)
{
	size_t bins = ht->num_bins * sizeof ht->bins[0];
	size_t items = ht->num_items * sizeof ht->items[0];
	size_t align = bins % MEM_ALIGNBYTES;

	if (align != 0)
		align = MEM_ALIGNBYTES - align;

	if (items_offset)
		*items_offset = bins + align;

	return bins + align + items;
}
