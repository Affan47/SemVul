gdImageCopyMergeGray (gdImagePtr dst, gdImagePtr src, int dstX, int dstY, int srcX, int srcY, int w, int h, int pct)
{
	int c, dc;
	int x, y;
	int tox, toy;
	int ncR, ncG, ncB;
	float g;
	toy = dstY;

	for (y = srcY; (y < (srcY + h)); y++) {
		tox = dstX;
		for (x = srcX; (x < (srcX + w)); x++) {
			int nc;
			c = gdImageGetPixel (src, x, y);

			if (gdImageGetTransparent(src) == c) {
				tox++;
				continue;
			}

			if (dst == src) {
				nc = c;
			} else {
				dc = gdImageGetPixel(dst, tox, toy);
				g = (0.29900f * gdImageRed(dst, dc)) + (0.58700f * gdImageGreen(dst, dc)) + (0.11400f * gdImageBlue(dst, dc));

				ncR = (int)(gdImageRed (src, c) * (pct / 100.0f) + gdImageRed(dst, dc) * g * ((100 - pct) / 100.0f));
				ncG = (int)(gdImageGreen (src, c) * (pct / 100.0f) + gdImageGreen(dst, dc) * g * ((100 - pct) / 100.0f));
				ncB = (int)(gdImageBlue (src, c) * (pct / 100.0f) + gdImageBlue(dst, dc) * g * ((100 - pct) / 100.0f));


				nc = gdImageColorExact(dst, ncR, ncG, ncB);
				if (nc == (-1)) {

					nc = gdImageColorAllocate(dst, ncR, ncG, ncB);

					if (nc == (-1)) {
						nc = gdImageColorClosest(dst, ncR, ncG, ncB);
					}
				}
			}
			gdImageSetPixel(dst, tox, toy, nc);
			tox++;
		}
		toy++;
	}
}
