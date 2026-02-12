DECLAREContigPutFunc(putcontig8bitYCbCr11tile)
{
	(void) y;
	fromskew *= 3;
	do {
		x = w;
		do {
			int32 Cb = pp[1];
			int32 Cr = pp[2];

			YCbCrtoRGB(*cp++, pp[0]);

			pp += 3;
		} while (--x);
		cp += toskew;
		pp += fromskew;
	} while (--h);
}
