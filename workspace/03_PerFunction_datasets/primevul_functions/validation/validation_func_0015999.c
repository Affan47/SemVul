static void rdp_write_gdiplus_cache_chunk_size(wStream* s, UINT16 gccs, UINT16 obccs, UINT16 opccs,
                                               UINT16 oiaccs)
{
	Stream_Write_UINT16(s, gccs);
	Stream_Write_UINT16(s, obccs);
	Stream_Write_UINT16(s, opccs);
	Stream_Write_UINT16(s, oiaccs);
}
