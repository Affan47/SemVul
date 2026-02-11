find_exact_renames(struct diff_options *options)
{
	int i;
	struct hash_table file_table;

	init_hash(&file_table);
	for (i = 0; i < rename_src_nr; i++)
		insert_file_table(&file_table, -1, i, rename_src[i].p->one);

	for (i = 0; i < rename_dst_nr; i++)
		insert_file_table(&file_table, 1, i, rename_dst[i].two);


	i = for_each_hash(&file_table, find_same_files, options);


	free_hash(&file_table);

	return i;
}
