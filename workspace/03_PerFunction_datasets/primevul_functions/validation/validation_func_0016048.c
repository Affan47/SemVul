static BOOL rdp_read_glyph_cache_capability_set(wStream* s, UINT16 length, rdpSettings* settings)
{
	if (length < 52)
		return FALSE;


	rdp_read_cache_definition(s, &(settings->GlyphCache[0]));
	rdp_read_cache_definition(s, &(settings->GlyphCache[1]));
	rdp_read_cache_definition(s, &(settings->GlyphCache[2]));
	rdp_read_cache_definition(s, &(settings->GlyphCache[3]));
	rdp_read_cache_definition(s, &(settings->GlyphCache[4]));
	rdp_read_cache_definition(s, &(settings->GlyphCache[5]));
	rdp_read_cache_definition(s, &(settings->GlyphCache[6]));
	rdp_read_cache_definition(s, &(settings->GlyphCache[7]));
	rdp_read_cache_definition(s, &(settings->GlyphCache[8]));
	rdp_read_cache_definition(s, &(settings->GlyphCache[9]));
	rdp_read_cache_definition(s, settings->FragCache);
	Stream_Read_UINT16(s, settings->GlyphSupportLevel);
	Stream_Seek_UINT16(s);
	return TRUE;
}
