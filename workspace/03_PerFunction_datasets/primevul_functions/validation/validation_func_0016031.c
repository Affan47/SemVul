static BOOL rdp_print_bitmap_cache_v2_capability_set(wStream* s, UINT16 length)
{
	UINT16 cacheFlags;
	BYTE pad2;
	BYTE numCellCaches;
	BITMAP_CACHE_V2_CELL_INFO bitmapCacheV2CellInfo[5];
	WLog_INFO(TAG, "BitmapCacheV2CapabilitySet (length %" PRIu16 "):", length);

	if (length < 40)
		return FALSE;

	Stream_Read_UINT16(s, cacheFlags);
	Stream_Read_UINT8(s, pad2);
	Stream_Read_UINT8(s, numCellCaches);
	rdp_read_bitmap_cache_cell_info(s,
	                                &bitmapCacheV2CellInfo[0]);
	rdp_read_bitmap_cache_cell_info(s,
	                                &bitmapCacheV2CellInfo[1]);
	rdp_read_bitmap_cache_cell_info(s,
	                                &bitmapCacheV2CellInfo[2]);
	rdp_read_bitmap_cache_cell_info(s,
	                                &bitmapCacheV2CellInfo[3]);
	rdp_read_bitmap_cache_cell_info(s,
	                                &bitmapCacheV2CellInfo[4]);
	Stream_Seek(s, 12);
	WLog_INFO(TAG, "\tcacheFlags: 0x%04" PRIX16 "", cacheFlags);
	WLog_INFO(TAG, "\tpad2: 0x%02" PRIX8 "", pad2);
	WLog_INFO(TAG, "\tnumCellCaches: 0x%02" PRIX8 "", numCellCaches);
	WLog_INFO(TAG, "\tbitmapCache0CellInfo: numEntries: %" PRIu32 " persistent: %" PRId32 "",
	          bitmapCacheV2CellInfo[0].numEntries, bitmapCacheV2CellInfo[0].persistent);
	WLog_INFO(TAG, "\tbitmapCache1CellInfo: numEntries: %" PRIu32 " persistent: %" PRId32 "",
	          bitmapCacheV2CellInfo[1].numEntries, bitmapCacheV2CellInfo[1].persistent);
	WLog_INFO(TAG, "\tbitmapCache2CellInfo: numEntries: %" PRIu32 " persistent: %" PRId32 "",
	          bitmapCacheV2CellInfo[2].numEntries, bitmapCacheV2CellInfo[2].persistent);
	WLog_INFO(TAG, "\tbitmapCache3CellInfo: numEntries: %" PRIu32 " persistent: %" PRId32 "",
	          bitmapCacheV2CellInfo[3].numEntries, bitmapCacheV2CellInfo[3].persistent);
	WLog_INFO(TAG, "\tbitmapCache4CellInfo: numEntries: %" PRIu32 " persistent: %" PRId32 "",
	          bitmapCacheV2CellInfo[4].numEntries, bitmapCacheV2CellInfo[4].persistent);
	return TRUE;
}
