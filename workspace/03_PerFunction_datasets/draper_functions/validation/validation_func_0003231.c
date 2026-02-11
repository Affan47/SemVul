draw_rle_fast(UINT16 *base, UINT16 color)
{
	UINT8 *src = &grom_base[(grom_bank | ((VIDEO_TRANSFER_ADDRHI & 0xff) << 16) | VIDEO_TRANSFER_ADDRLO) % grom_size];
	int transparent_pen = (VIDEO_TRANSFER_FLAGS & XFERFLAG_TRANSPARENT) ? 0xff : -1;
	int width = VIDEO_TRANSFER_WIDTH;
	int height = ADJUSTED_HEIGHT(VIDEO_TRANSFER_HEIGHT);
	int sx = VIDEO_TRANSFER_X & 0xfff;
	int sy = (VIDEO_TRANSFER_Y & 0xfff) << 8;
	int xleft, y, count = 0, val = 0, innercount;
	int ydststep = VIDEO_DST_YSTEP;
	int lclip, rclip;


	lclip = clip_rect.min_x - sx;
	if (lclip < 0) lclip = 0;
	rclip = sx + width - clip_rect.max_x;
	if (rclip < 0) rclip = 0;
	width -= lclip + rclip;
	sx += lclip;


	if (VIDEO_TRANSFER_FLAGS & XFERFLAG_YFLIP)
		ydststep = -ydststep;


	for (y = 0; y < height; y++, sy += ydststep)
	{
		UINT16 *dstbase;


		if (sy < scaled_clip_rect.min_y || sy >= scaled_clip_rect.max_y)
		{
			SKIP_RLE(width + lclip + rclip, xleft, count, innercount, src);
			continue;
		}


		dstbase = &base[compute_safe_address(sx, sy >> 8)];


		SKIP_RLE(lclip, xleft, count, innercount, src);


		for (xleft = width; xleft > 0; )
		{

			GET_NEXT_RUN(xleft, count, innercount, src);


			if (val == -1)
				while (innercount--)
				{
					int pixel = *src++;
					if (pixel != transparent_pen)
						*dstbase = color | pixel;
					dstbase++;
				}


			else if (val != transparent_pen)
			{
				val |= color;
				while (innercount--)
					*dstbase++ = val;
			}


			else
				dstbase += innercount;
		}


		SKIP_RLE(rclip, xleft, count, innercount, src);
	}
}
