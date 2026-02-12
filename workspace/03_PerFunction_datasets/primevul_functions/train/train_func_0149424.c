static int _gdImageBmpCtx(gdImagePtr im, gdIOCtxPtr out, int compression)
{
	int bitmap_size = 0, info_size, total_size, padding;
	int i, row, xpos, pixel;
	int error = 0;
	unsigned char *uncompressed_row = NULL, *uncompressed_row_start = NULL;
	FILE *tmpfile_for_compression = NULL;
	gdIOCtxPtr out_original = NULL;
	int ret = 1;


	if (im->trueColor) {
		compression = 0;
	}

	if (compression && !out->seek) {

		if ((tmpfile_for_compression = tmpfile()) == NULL) {
			compression = 0;
		} else {
			out_original = out;
			if ((out = (gdIOCtxPtr)gdNewFileCtx(tmpfile_for_compression)) == NULL) {
				out = out_original;
				out_original = NULL;
				compression = 0;
			}
		}
	}

	bitmap_size = ((im->sx * (im->trueColor ? 24 : 8)) / 8) * im->sy;


	info_size = BMP_WINDOWS_V3;


	if (!im->trueColor) {
		info_size += im->colorsTotal * 4;
		if (compression) {
			bitmap_size = 0;
		}
	}


	total_size = 14 + info_size + bitmap_size;


	gdPutBuf("BM", 2, out);
	gdBMPPutInt(out, total_size);
	gdBMPPutWord(out, 0);
	gdBMPPutWord(out, 0);
	gdBMPPutInt(out, 14 + info_size);


	gdBMPPutInt(out, BMP_WINDOWS_V3);
	gdBMPPutInt(out, im->sx);
	gdBMPPutInt(out, im->sy);
	gdBMPPutWord(out, 1);
	gdBMPPutWord(out, (im->trueColor ? 24 : 8));
	gdBMPPutInt(out, (compression ? BMP_BI_RLE8 : BMP_BI_RGB));
	gdBMPPutInt(out, bitmap_size);
	gdBMPPutInt(out, 0);
	gdBMPPutInt(out, 0);
	gdBMPPutInt(out, im->colorsTotal);
	gdBMPPutInt(out, 0);


	padding = ((int)(im->trueColor ? 3 : 1) * im->sx) % 4;
	if (padding) {
		padding = 4 - padding;
	}


	if (!im->trueColor) {
		for(i = 0; i< im->colorsTotal; ++i) {
			Putchar(gdImageBlue(im, i), out);
			Putchar(gdImageGreen(im, i), out);
			Putchar(gdImageRed(im, i), out);
			Putchar(0, out);
		}

		if (compression) {

			uncompressed_row = uncompressed_row_start = (unsigned char *) gdCalloc(gdImageSX(im) * 2, sizeof(char));
			if (!uncompressed_row) {

				goto cleanup;
			}
		}

		for (row = (im->sy - 1); row >= 0; row--) {
			if (compression) {
				memset (uncompressed_row, 0, gdImageSX(im));
			}

			for (xpos = 0; xpos < im->sx; xpos++) {
				if (compression) {
					*uncompressed_row++ = (unsigned char)gdImageGetPixel(im, xpos, row);
				} else {
					Putchar(gdImageGetPixel(im, xpos, row), out);
				}
			}

			if (!compression) {

				for (xpos = padding; xpos > 0; --xpos) {
					Putchar('\0', out);
				}
			} else {
				int compressed_size = 0;
				uncompressed_row = uncompressed_row_start;
				if ((compressed_size = compress_row(uncompressed_row, gdImageSX(im))) < 0) {
					error = 1;
					break;
				}
				bitmap_size += compressed_size;


				gdPutBuf(uncompressed_row, compressed_size, out);
				Putchar(BMP_RLE_COMMAND, out);
				Putchar(BMP_RLE_ENDOFLINE, out);
				bitmap_size += 2;
			}
		}

		if (compression && uncompressed_row) {
			gdFree(uncompressed_row);
			if (error != 0) {
				goto cleanup;
			}

			Putchar(BMP_RLE_COMMAND, out);
			Putchar(BMP_RLE_ENDOFBITMAP, out);
			bitmap_size += 2;


			gdSeek(out, 2);
			gdBMPPutInt(out, total_size + bitmap_size);


			gdSeek(out, 34);
			gdBMPPutInt(out, bitmap_size);
		}

	} else {
		for (row = (im->sy - 1); row >= 0; row--) {
			for (xpos = 0; xpos < im->sx; xpos++) {
				pixel = gdImageGetPixel(im, xpos, row);

				Putchar(gdTrueColorGetBlue(pixel), out);
				Putchar(gdTrueColorGetGreen(pixel), out);
				Putchar(gdTrueColorGetRed(pixel), out);
			}


			for (xpos = padding; xpos > 0; --xpos) {
				Putchar('\0', out);
			}
		}
	}


	if (tmpfile_for_compression) {
		unsigned char* copy_buffer = NULL;
		int buffer_size = 0;

		gdSeek(out, 0);
		copy_buffer = (unsigned char *) gdMalloc(1024 * sizeof(unsigned char));
		if (copy_buffer == NULL) {
			goto cleanup;
		}

		while ((buffer_size = gdGetBuf(copy_buffer, 1024, out)) != EOF) {
			if (buffer_size == 0) {
				break;
			}
			gdPutBuf(copy_buffer , buffer_size, out_original);
		}
		gdFree(copy_buffer);


		out->gd_free(out);
		out = out_original;
		out_original = NULL;
	}

	ret = 0;
cleanup:
	if (tmpfile_for_compression) {
#ifdef _WIN32
		_rmtmp();
#else
		fclose(tmpfile_for_compression);
#endif
		tmpfile_for_compression = NULL;
	}

	if (out_original) {
		out_original->gd_free(out_original);
	}
	return ret;
}
