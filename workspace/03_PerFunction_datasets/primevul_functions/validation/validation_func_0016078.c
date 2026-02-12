static void rdp_write_gdiplus_image_cache_properties(wStream* s, UINT16 oiccs, UINT16 oicts,
                                                     UINT16 oicms)
{
	Stream_Write_UINT16(s, oiccs);
	Stream_Write_UINT16(s, oicts);
	Stream_Write_UINT16(s, oicms);
}
