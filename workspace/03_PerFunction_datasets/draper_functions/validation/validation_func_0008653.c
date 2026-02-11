_gdGetColors (gdIOCtx * in, gdImagePtr im, int gd2xFlag)
{
	int i;
	if (gd2xFlag) {
		int trueColorFlag;
		if (!gdGetByte (&trueColorFlag, in)) {
			goto fail1;
		}


		if (trueColorFlag != im->trueColor) {
			goto fail1;
		}

		if (!im->trueColor) {
			if (!gdGetWord (&im->colorsTotal, in)) {
				goto fail1;
			}
			if (im->colorsTotal > gdMaxColors) {
				goto fail1;
			}
		}

		if (!gdGetInt (&im->transparent, in)) {
			goto fail1;
		}
	} else {
		if (!gdGetByte (&im->colorsTotal, in)) {
			goto fail1;
		}
		if (!gdGetWord (&im->transparent, in)) {
			goto fail1;
		}
		if (im->transparent == 257) {
			im->transparent = (-1);
		}
	}
	GD2_DBG (printf
	         ("Palette had %d colours (T=%d)\n", im->colorsTotal,
	          im->transparent));
	if (im->trueColor) {
		return TRUE;
	}
	for (i = 0; (i < gdMaxColors); i++) {
		if (!gdGetByte (&im->red[i], in)) {
			goto fail1;
		}
		if (!gdGetByte (&im->green[i], in)) {
			goto fail1;
		}
		if (!gdGetByte (&im->blue[i], in)) {
			goto fail1;
		}
		if (gd2xFlag) {
			if (!gdGetByte (&im->alpha[i], in)) {
				goto fail1;
			}
		}
	}

	for (i = 0; (i < im->colorsTotal); i++) {
		im->open[i] = 0;
	};

	return TRUE;
fail1:
	return FALSE;
}
