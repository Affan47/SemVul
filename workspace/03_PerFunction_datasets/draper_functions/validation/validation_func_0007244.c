get_from_size_list (LOSFreeChunks **list, size_t size)
{
	LOSFreeChunks *free_chunks = NULL;
	LOSSection *section;
	int num_chunks, i, start_index;

	g_assert ((size & (LOS_CHUNK_SIZE - 1)) == 0);

	while (*list) {
		free_chunks = *list;
		if (free_chunks->size >= size)
			break;
		list = &(*list)->next_size;
	}

	if (!*list)
		return NULL;

	*list = free_chunks->next_size;

	if (free_chunks->size > size)
		add_free_chunk ((LOSFreeChunks*)((char*)free_chunks + size), free_chunks->size - size);

	num_chunks = size >> LOS_CHUNK_BITS;

	section = LOS_SECTION_FOR_OBJ (free_chunks);

	start_index = LOS_CHUNK_INDEX (free_chunks, section);
	for (i = start_index; i < start_index + num_chunks; ++i) {
		g_assert (section->free_chunk_map [i]);
		section->free_chunk_map [i] = 0;
	}

	section->num_free_chunks -= size >> LOS_CHUNK_BITS;
	g_assert (section->num_free_chunks >= 0);

	return free_chunks;
}
