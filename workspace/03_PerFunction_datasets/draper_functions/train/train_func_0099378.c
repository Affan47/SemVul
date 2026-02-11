nfs_readdir_add_to_array(struct nfs_entry *entry, struct page *page)
{
	struct nfs_cache_array *array = nfs_readdir_get_array(page);
	struct nfs_cache_array_entry *cache_entry;
	int ret;

	if (IS_ERR(array))
		return PTR_ERR(array);

	cache_entry = &array->array[array->size];


	ret = -ENOSPC;
	if ((char *)&cache_entry[1] - (char *)page_address(page) > PAGE_SIZE)
		goto out;

	cache_entry->cookie = entry->prev_cookie;
	cache_entry->ino = entry->ino;
	cache_entry->d_type = entry->d_type;
	ret = nfs_readdir_make_qstr(&cache_entry->string, entry->name, entry->len);
	if (ret)
		goto out;
	array->last_cookie = entry->cookie;
	array->size++;
	if (entry->eof != 0)
		array->eof_index = array->size;
out:
	nfs_readdir_release_array(page);
	return ret;
}
