static void rdp_write_gdiplus_cache_entries(wStream* s, UINT16 gce, UINT16 bce, UINT16 pce,
                                            UINT16 ice, UINT16 ace)
{
	Stream_Write_UINT16(s, gce);
	Stream_Write_UINT16(s, bce);
	Stream_Write_UINT16(s, pce);
	Stream_Write_UINT16(s, ice);
	Stream_Write_UINT16(s, ace);
}
