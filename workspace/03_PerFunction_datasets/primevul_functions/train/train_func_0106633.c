static void gdImageAALine (gdImagePtr im, int x1, int y1, int x2, int y2, int col)
{

	long x, y, inc;
	long dx, dy,tmp;
	if (!im->trueColor) {

		gdImageLine(im, x1, y1, x2, y2, col);
		return;
	}

        if (clip_1d (&x1, &y1, &x2, &y2, im->cx1, im->cx2) == 0)
          return;
        if (clip_1d (&y1, &x1, &y2, &x2, im->cy1, im->cy2) == 0)
          return;
	dx = x2 - x1;
	dy = y2 - y1;

	if (dx == 0 && dy == 0) {

		gdImageSetAAPixelColor(im, x1, y1, col, 0xFF);
		return;
	}
	if (abs(dx) > abs(dy)) {
		if (dx < 0) {
			tmp = x1;
			x1 = x2;
			x2 = tmp;
			tmp = y1;
			y1 = y2;
			y2 = tmp;
			dx = x2 - x1;
			dy = y2 - y1;
		}
		x = x1 << 16;
		y = y1 << 16;
		inc = (dy * 65536) / dx;

		while ((x >> 16) <= x2) {
			gdImageSetAAPixelColor(im, x >> 16, y >> 16, col, (y >> 8) & 0xFF);
			gdImageSetAAPixelColor(im, x >> 16, (y >> 16) + 1,col, (~y >> 8) & 0xFF);
			x += (1 << 16);
			y += inc;
		}
	} else {
		if (dy < 0) {
			tmp = x1;
			x1 = x2;
			x2 = tmp;
			tmp = y1;
			y1 = y2;
			y2 = tmp;
			dx = x2 - x1;
			dy = y2 - y1;
		}
		x = x1 << 16;
		y = y1 << 16;
		inc = (dx * 65536) / dy;

		while ((y>>16) <= y2) {
			gdImageSetAAPixelColor(im, x >> 16, y >> 16, col, (x >> 8) & 0xFF);
			gdImageSetAAPixelColor(im, (x >> 16) + 1, (y >> 16),col, (~x >> 8) & 0xFF);
			x += inc;
			y += (1<<16);
		}
	}
}
