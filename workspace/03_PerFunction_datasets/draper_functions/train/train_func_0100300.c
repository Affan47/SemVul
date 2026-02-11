gkrellm_scale_piximage_to_pixmap(GkrellmPiximage *piximage, GdkPixmap **pixmap,
			GdkBitmap **mask, gint w_dst, gint h_dst)
	{
	GdkWindow		*window = gkrellm_get_top_window()->window;
	GdkPixbuf		*src_pixbuf, *dst_pixbuf;
	gint			w_src, h_src;
	gboolean		has_alpha;


	gkrellm_free_pixmap(pixmap);
	gkrellm_free_bitmap(mask);

	if (!piximage || !piximage->pixbuf || !pixmap)
		return FALSE;

	src_pixbuf = piximage->pixbuf;
	has_alpha = gdk_pixbuf_get_has_alpha(src_pixbuf);
	w_src = gdk_pixbuf_get_width(src_pixbuf);
	h_src = gdk_pixbuf_get_height(src_pixbuf);

	if (w_dst == 0)
		w_dst = w_src;
	else if (w_dst < 0 && (w_dst = w_src * _GK.theme_scale / 100) <= 0)
		w_dst = 1;

	if (h_dst == 0)
		h_dst = h_src;
	else if (h_dst < 0 && (h_dst = h_src * _GK.theme_scale / 100) <= 0)
		h_dst = 1;

	*pixmap = gdk_pixmap_new(window, w_dst, h_dst, -1);
	if (mask && has_alpha)
		*mask = gdk_pixmap_new(window, w_dst, h_dst, 1);

	if (w_dst == w_src && h_dst == h_src)
		{
		_render_to_pixmap(src_pixbuf, pixmap, mask, 0, 0, 0, 0, w_dst, h_dst);
		return TRUE;
		}

	dst_pixbuf = gkrellm_scale_piximage_to_pixbuf(piximage, w_dst, h_dst);
	_render_to_pixmap(dst_pixbuf, pixmap, mask, 0, 0, 0, 0, w_dst, h_dst);

	g_object_unref(G_OBJECT(dst_pixbuf));
	return TRUE;
	}
