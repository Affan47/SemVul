static void rdp_read_cache_definition(wStream* s, GLYPH_CACHE_DEFINITION* cache_definition)
{
	Stream_Read_UINT16(s, cache_definition->cacheEntries);
	Stream_Read_UINT16(s,
	                   cache_definition->cacheMaximumCellSize);
}
