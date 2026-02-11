GdipGetFontCollectionFamilyList (GpFontCollection *font_collection, int num_sought, GpFontFamily *gpfamilies[], int *num_found)
{
	int i;

	if (!font_collection || !gpfamilies || !num_found)
		return InvalidParameter;

	if (font_collection->config)
		gdip_createPrivateFontSet (font_collection);

	for (i = 0; i < font_collection->fontset->nfont; i++) {
		gdip_createFontFamily(&gpfamilies[i]);
		gpfamilies[i]->pattern = font_collection->fontset->fonts[i];
		gpfamilies[i]->allocated = FALSE;
	}

	*num_found = font_collection->fontset->nfont;
	return Ok;
}
