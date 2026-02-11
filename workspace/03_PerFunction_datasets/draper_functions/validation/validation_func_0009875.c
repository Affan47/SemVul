get_process_ht(hash_table_t * fd_mappings, int32_t pid) {
	process_hash_item_t * p_item;
	item_t * process_ht_item;

	if ( (process_ht_item = hash_table_find(fd_mappings, &pid)) != NULL ) {
		p_item = hash_table_entry(process_ht_item, process_hash_item_t, item);
		if ( pid == p_item->pid) {
			return (p_item->ht);
		}
	}
	return NULL;
}
