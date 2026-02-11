fswc_add_image_jpeg(src_t *src, avgbmp_t *abitmap)
{
	uint32_t x, y, hlength;
	uint8_t *himg = NULL;
	gdImage *im;
	int i;


	i = verify_jpeg_dht(src->img, src->length, &himg, &hlength);

	im = gdImageCreateFromJpegPtr(hlength, himg);
	if(i == 1) free(himg);

	if(!im) return(-1);

	for(y = 0; y < src->height; y++)
		for(x = 0; x < src->width; x++)
		{
			int c = gdImageGetPixel(im, x, y);

			*(abitmap++) += (c & 0xFF0000) >> 16;
			*(abitmap++) += (c & 0x00FF00) >> 8;
			*(abitmap++) += (c & 0x0000FF);
		}

	gdImageDestroy(im);

	return(0);
}
