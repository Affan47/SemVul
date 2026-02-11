fz_copy_ft_bitmap(fz_context *ctx, int left, int top, FT_Bitmap *bitmap)
{
	fz_pixmap *pixmap;
	int y;

	pixmap = fz_new_pixmap(ctx, NULL, bitmap->width, bitmap->rows);
	pixmap->x = left;
	pixmap->y = top - bitmap->rows;

	if (bitmap->pixel_mode == FT_PIXEL_MODE_MONO)
	{
		for (y = 0; y < pixmap->h; y++)
		{
			unsigned char *out = pixmap->samples + (unsigned int)(y * pixmap->w);
			unsigned char *in = bitmap->buffer + (unsigned int)((pixmap->h - y - 1) * bitmap->pitch);
			unsigned char bit = 0x80;
			int w = pixmap->w;
			while (w--)
			{
				*out++ = (*in & bit) ? 255 : 0;
				bit >>= 1;
				if (bit == 0)
				{
					bit = 0x80;
					in++;
				}
			}
		}
	}
	else
	{
		for (y = 0; y < pixmap->h; y++)
		{
			memcpy(pixmap->samples + (unsigned int)(y * pixmap->w),
				bitmap->buffer + (unsigned int)((pixmap->h - y - 1) * bitmap->pitch),
				pixmap->w);
		}
	}

	return pixmap;
}
