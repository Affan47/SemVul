unsigned headerSizeof(Header h, int magicp)
{
    indexEntry entry;
    unsigned int size = 0;
    int i;

    if (h == NULL)
	return size;

    headerSort(h);

    if (magicp == HEADER_MAGIC_YES)
	size += sizeof(rpm_header_magic);

    size += 2 * sizeof(int32_t);

    for (i = 0, entry = h->index; i < h->indexUsed; i++, entry++) {

        if (ENTRY_IS_REGION(entry)) {
	    size += entry->length;

	    if (i == 0 && (h->flags & HEADERFLAG_LEGACY))
		size += sizeof(struct entryInfo_s) + entry->info.count;
	    continue;
        }


	if (entry->info.offset < 0)
	    continue;


	size += alignDiff(entry->info.type, size);

	size += sizeof(struct entryInfo_s) + entry->length;
    }

    return size;
}
