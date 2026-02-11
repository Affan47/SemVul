SpGistInitMetapage(Page page)
{
	SpGistMetaPageData *metadata;
	int			i;

	SpGistInitPage(page, SPGIST_META);
	metadata = SpGistPageGetMeta(page);
	memset(metadata, 0, sizeof(SpGistMetaPageData));
	metadata->magicNumber = SPGIST_MAGIC_NUMBER;


	for (i = 0; i < SPGIST_CACHED_PAGES; i++)
		metadata->lastUsedPages.cachedPage[i].blkno = InvalidBlockNumber;
}
