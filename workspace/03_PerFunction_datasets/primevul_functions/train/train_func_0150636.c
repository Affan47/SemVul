static int _gdImagePngCtxEx(gdImagePtr im, gdIOCtx * outfile, int level)
{
	int i, j, bit_depth = 0, interlace_type;
	int width = im->sx;
	int height = im->sy;
	int colors = im->colorsTotal;
	int *open = im->open;
	int mapping[gdMaxColors];
	png_byte trans_values[256];
	png_color_16 trans_rgb_value;
	png_color palette[gdMaxColors];
	png_structp png_ptr;
	png_infop info_ptr;
	volatile int transparent = im->transparent;
	volatile int remap = FALSE;
#ifdef PNG_SETJMP_SUPPORTED
	jmpbuf_wrapper jbw;
#endif
	int ret = 0;


	if (width == 0 || height ==0) return 1;

#ifdef PNG_SETJMP_SUPPORTED
	png_ptr = png_create_write_struct (PNG_LIBPNG_VER_STRING,
	                                   &jbw, gdPngErrorHandler,
	                                   NULL);
#else
	png_ptr = png_create_write_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
#endif
	if (png_ptr == NULL) {
		gd_error("gd-png error: cannot allocate libpng main struct\n");
		return 1;
	}

	info_ptr = png_create_info_struct (png_ptr);
	if (info_ptr == NULL) {
		gd_error("gd-png error: cannot allocate libpng info struct\n");
		png_destroy_write_struct (&png_ptr, (png_infopp) NULL);
		return 1;
	}

#ifdef PNG_SETJMP_SUPPORTED
	if (setjmp(jbw.jmpbuf)) {
		gd_error("gd-png error: setjmp returns error condition\n");
		png_destroy_write_struct (&png_ptr, &info_ptr);
		return 1;
	}
#endif

	png_set_write_fn (png_ptr, (void *) outfile, gdPngWriteData,
	                  gdPngFlushData);


#if 0
	png_set_filter (png_ptr, 0, PNG_FILTER_NONE);
#endif


	png_set_compression_level (png_ptr, level);

#ifdef PNG_pHYs_SUPPORTED

	png_set_pHYs(png_ptr, info_ptr, DPI2DPM(im->res_x), DPI2DPM(im->res_y),
	             PNG_RESOLUTION_METER);
#endif


	if (!im->trueColor) {
		if (transparent >= im->colorsTotal ||
		        (transparent >= 0 && open[transparent]))
			transparent = -1;
	}
	if (!im->trueColor) {
		for (i = 0; i < gdMaxColors; ++i)
			mapping[i] = -1;
	}
	if (!im->trueColor) {

		colors = 0;
		for (i = 0; i < im->colorsTotal; ++i) {
			if (!open[i]) {
				mapping[i] = colors;
				++colors;
			}
		}
		if (colors == 0) {
			gd_error("gd-png error: no colors in palette\n");
			ret = 1;
			goto bail;
		}
		if (colors < im->colorsTotal) {
			remap = TRUE;
		}
		if (colors <= 2)
			bit_depth = 1;
		else if (colors <= 4)
			bit_depth = 2;
		else if (colors <= 16)
			bit_depth = 4;
		else
			bit_depth = 8;
	}
	interlace_type = im->interlace ? PNG_INTERLACE_ADAM7 : PNG_INTERLACE_NONE;

	if (im->trueColor) {
		if (im->saveAlphaFlag) {
			png_set_IHDR (png_ptr, info_ptr, width, height, 8,
			              PNG_COLOR_TYPE_RGB_ALPHA, interlace_type,
			              PNG_COMPRESSION_TYPE_DEFAULT,
			              PNG_FILTER_TYPE_DEFAULT);
		} else {
			png_set_IHDR (png_ptr, info_ptr, width, height, 8,
			              PNG_COLOR_TYPE_RGB, interlace_type,
			              PNG_COMPRESSION_TYPE_DEFAULT,
			              PNG_FILTER_TYPE_DEFAULT);
		}
	} else {
		png_set_IHDR (png_ptr, info_ptr, width, height, bit_depth,
		              PNG_COLOR_TYPE_PALETTE, interlace_type,
		              PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
	}
	if (im->trueColor && (!im->saveAlphaFlag) && (transparent >= 0)) {

		trans_rgb_value.red = gdTrueColorGetRed (im->transparent);
		trans_rgb_value.green = gdTrueColorGetGreen (im->transparent);
		trans_rgb_value.blue = gdTrueColorGetBlue (im->transparent);
		png_set_tRNS (png_ptr, info_ptr, 0, 0, &trans_rgb_value);
	}
	if (!im->trueColor) {


		int tc = 0;
		int i;
		int j;
		int k;
		for (i = 0; (i < im->colorsTotal); i++) {
			if ((!im->open[i]) && (im->alpha[i] != gdAlphaOpaque)) {
				tc++;
			}
		}
		if (tc) {
#if 0
			for (i = 0; (i < im->colorsTotal); i++) {
				trans_values[i] = 255 -
				                  ((im->alpha[i] << 1) + (im->alpha[i] >> 6));
			}
			png_set_tRNS (png_ptr, info_ptr, trans_values, 256, NULL);
#endif
			if (!remap) {
				remap = TRUE;
			}


			j = 0;
			k = colors - 1;
			for (i = 0; (i < im->colorsTotal); i++) {
				if (!im->open[i]) {
					if (im->alpha[i] != gdAlphaOpaque) {

						trans_values[j] = 255 -
						                  ((im->alpha[i] << 1) + (im->alpha[i] >> 6));
						mapping[i] = j++;
					} else {
						mapping[i] = k--;
					}
				}
			}
			png_set_tRNS (png_ptr, info_ptr, trans_values, tc, NULL);
		}
	}


	if (!im->trueColor) {
		if (remap)
			for (i = 0; i < im->colorsTotal; ++i) {
				if (mapping[i] < 0)
					continue;
				palette[mapping[i]].red = im->red[i];
				palette[mapping[i]].green = im->green[i];
				palette[mapping[i]].blue = im->blue[i];
			}
		else
			for (i = 0; i < colors; ++i) {
				palette[i].red = im->red[i];
				palette[i].green = im->green[i];
				palette[i].blue = im->blue[i];
			}
		png_set_PLTE (png_ptr, info_ptr, palette, colors);
	}


	png_write_info (png_ptr, info_ptr);


	png_set_packing (png_ptr);


	if (im->trueColor) {

		int channels = im->saveAlphaFlag ? 4 : 3;

		png_bytep *row_pointers;
		unsigned char *pOutputRow;
		int **ptpixels = im->tpixels;
		int *pThisRow;
		unsigned char a;
		int thisPixel;
		png_bytep *prow_pointers;
		int saveAlphaFlag = im->saveAlphaFlag;
		if (overflow2(sizeof (png_bytep), height)) {
			ret = 1;
			goto bail;
		}
		row_pointers = gdMalloc (sizeof (png_bytep) * height);
		if (row_pointers == NULL) {
			gd_error("gd-png error: unable to allocate row_pointers\n");
			ret = 1;
			goto bail;
		}
		prow_pointers = row_pointers;
		for (j = 0; j < height; ++j) {
			if (overflow2(width, channels) || ((*prow_pointers =
			                                        (png_bytep) gdMalloc (width * channels)) == NULL)) {
				gd_error("gd-png error: unable to allocate rows\n");
				for (i = 0; i < j; ++i)
					gdFree (row_pointers[i]);

				gdFree(row_pointers);
				ret = 1;
				goto bail;
			}
			pOutputRow = *prow_pointers++;
			pThisRow = *ptpixels++;
			for (i = 0; i < width; ++i) {
				thisPixel = *pThisRow++;
				*pOutputRow++ = gdTrueColorGetRed (thisPixel);
				*pOutputRow++ = gdTrueColorGetGreen (thisPixel);
				*pOutputRow++ = gdTrueColorGetBlue (thisPixel);

				if (saveAlphaFlag) {


					a = gdTrueColorGetAlpha (thisPixel);

					*pOutputRow++ = 255 - ((a << 1) + (a >> 6));
				}
			}
		}

		png_write_image (png_ptr, row_pointers);
		png_write_end (png_ptr, info_ptr);

		for (j = 0; j < height; ++j)
			gdFree (row_pointers[j]);
		gdFree (row_pointers);
	} else {
		if (remap) {
			png_bytep *row_pointers;
			if (overflow2(sizeof (png_bytep), height)) {
				ret = 1;
				goto bail;
			}
			row_pointers = gdMalloc (sizeof (png_bytep) * height);
			if (row_pointers == NULL) {
				gd_error("gd-png error: unable to allocate row_pointers\n");
				ret = 1;
				goto bail;
			}
			for (j = 0; j < height; ++j) {
				if ((row_pointers[j] = (png_bytep) gdMalloc (width)) == NULL) {
					gd_error("gd-png error: unable to allocate rows\n");
					for (i = 0; i < j; ++i)
						gdFree (row_pointers[i]);

					gdFree (row_pointers);
					ret = 1;
					goto bail;
				}
				for (i = 0; i < width; ++i)
					row_pointers[j][i] = mapping[im->pixels[j][i]];
			}

			png_write_image (png_ptr, row_pointers);
			png_write_end (png_ptr, info_ptr);

			for (j = 0; j < height; ++j)
				gdFree (row_pointers[j]);
			gdFree (row_pointers);
		} else {
			png_write_image (png_ptr, im->pixels);
			png_write_end (png_ptr, info_ptr);
		}
	}

bail:
	png_destroy_write_struct (&png_ptr, &info_ptr);
	return ret;
}
