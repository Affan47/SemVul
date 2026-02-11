fixup_prefs_dim2 (struct wh *wh)
{
	if (wh->width < 160)
		wh->width = 160;
	if (wh->height < 128)
		wh->height = 128;
	if (wh->width > 3072)
		wh->width = 3072;
	if (wh->height > 2048)
		wh->height = 2048;
}
