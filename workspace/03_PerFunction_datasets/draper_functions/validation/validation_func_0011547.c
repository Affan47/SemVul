pixbuf_draw_border(GdkPixbuf *pixbuf, gint w, gint h)
{
	gboolean alpha;
	gint rs;
	guchar *pix;
	guchar *p;
	gint i;

	alpha = gdk_pixbuf_get_has_alpha(pixbuf);
	rs = gdk_pixbuf_get_rowstride(pixbuf);
	pix = gdk_pixbuf_get_pixels(pixbuf);

	p = pix;
	for (i = 0; i < w; i++)
		{
		*p = 0; p++; *p = 0; p++; *p = 0; p++;
		if (alpha) { *p= 255; p++; }
		}
	for (i = 1; i < h - 1; i++)
		{
		p = pix + rs * i;
		*p = 0; p++; *p = 0; p++; *p = 0; p++;
		if (alpha) *p= 255;

		p = pix + rs * i + (w - 1) * ((alpha == TRUE) ? 4 : 3);
		*p = 0; p++; *p = 0; p++; *p = 0; p++;
		if (alpha) *p= 255;
		}
	p = pix + rs * (h - 1);
	for (i = 0; i < w; i++)
		{
		*p = 0; p++; *p = 0; p++; *p = 0; p++;
		if (alpha) { *p= 255; p++; }
		}
}
