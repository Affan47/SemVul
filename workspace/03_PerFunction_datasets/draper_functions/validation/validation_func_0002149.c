BitBlt_SPna_32bpp(HGDI_DC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, HGDI_DC hdcSrc, int nXSrc, int nYSrc)
{
	int x, y;
	uint8 *srcp;
	uint8 *dstp;
	uint8 *patp;

	for (y = 0; y < nHeight; y++)
	{
		srcp = gdi_get_bitmap_pointer(hdcSrc, nXSrc, nYSrc + y);
		dstp = gdi_get_bitmap_pointer(hdcDest, nXDest, nYDest + y);

		if (dstp != 0)
		{
			for (x = 0; x < nWidth; x++)
			{
				patp = gdi_get_brush_pointer(hdcDest, x, y);

				*dstp = *srcp & ~(*patp);
				patp++;
				srcp++;
				dstp++;

				*dstp = *srcp & ~(*patp);
				patp++;
				srcp++;
				dstp++;

				*dstp = *srcp & ~(*patp);
				srcp += 2;
				dstp += 2;
			}
		}
	}

	return 0;
}
