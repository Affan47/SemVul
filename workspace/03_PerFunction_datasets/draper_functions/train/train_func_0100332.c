update_read_cache_color_table_order(STREAM* s, CACHE_COLOR_TABLE_ORDER* cache_color_table_order, uint16 flags)
{
	int i;
	uint32* colorTable;

	stream_read_uint8(s, cache_color_table_order->cacheIndex);
	stream_read_uint8(s, cache_color_table_order->numberColors);

	colorTable = cache_color_table_order->colorTable;

	if (colorTable == NULL)
		colorTable = (uint32*) xmalloc(cache_color_table_order->numberColors * 4);
	else
		colorTable = (uint32*) xrealloc(colorTable, cache_color_table_order->numberColors * 4);

	for (i = 0; i < cache_color_table_order->numberColors; i++)
	{
		update_read_color_quad(s, &colorTable[i]);
	}

	cache_color_table_order->colorTable = colorTable;
}
