poppler_fonts_iter_free (PopplerFontsIter *iter)
{
	if (G_UNLIKELY (iter == NULL))
		return;

	deleteGooList (iter->items, FontInfo);

	g_slice_free (PopplerFontsIter, iter);
}
