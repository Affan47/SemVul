gdk_pixbuf__bmp_image_save_to_callback (GdkPixbufSaveFunc   save_func,
					gpointer            user_data,
					GdkPixbuf          *pixbuf,
					gchar             **keys,
					gchar             **values,
					GError            **error)
{
	guint width, height, channel, size, stride, src_stride, x, y;
	guchar BFH_BIH[54], *pixels, *buf, *src, *dst, *dst_line;
	gboolean ret;

	width = gdk_pixbuf_get_width (pixbuf);
	height = gdk_pixbuf_get_height (pixbuf);
	channel = gdk_pixbuf_get_n_channels (pixbuf);
	pixels = gdk_pixbuf_get_pixels (pixbuf);
	src_stride = gdk_pixbuf_get_rowstride (pixbuf);
	stride = (width * 3 + 3) & ~3;
	size = stride * height;


	dst = BFH_BIH;
	*dst++ = 'B';
	*dst++ = 'M';
	put32 (dst, size + 14 + 40);
	put32 (dst, 0);
	put32 (dst, 14 + 40);


	put32 (dst, 40);
	put32 (dst, width);
	put32 (dst, height);
	put16 (dst, 1);
	put16 (dst, 24);
	put32 (dst, BI_RGB);
	put32 (dst, size);
	put32 (dst, 0);
	put32 (dst, 0);
	put32 (dst, 0);
	put32 (dst, 0);

	if (!save_func ((gchar *)BFH_BIH, 14 + 40, error, user_data))
		return FALSE;

	dst_line = buf = g_try_malloc (size);
	if (!buf) {
		g_set_error_literal (error,
                                     GDK_PIXBUF_ERROR,
                                     GDK_PIXBUF_ERROR_INSUFFICIENT_MEMORY,
                                     _("Couldn't allocate memory for saving BMP file"));
		return FALSE;
	}


	pixels += (height - 1) * src_stride;
	for (y = 0; y < height; ++y, pixels -= src_stride, dst_line += stride) {
		dst = dst_line;
		src = pixels;
		for (x = 0; x < width; ++x, dst += 3, src += channel) {
			dst[0] = src[2];
			dst[1] = src[1];
			dst[2] = src[0];
		}
	}
	ret = save_func ((gchar *)buf, size, error, user_data);
	g_free (buf);

	return ret;
}
