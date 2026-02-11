reduce (BYTE* source, int width, int height, BYTE *dest)
{
	int i, j, n = 0, value = 0;

	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			int pos = (i * width + j) * 4;
			BYTE combine = source [pos] | source [pos + 1] | source [pos + 2] | source [pos + 3];

			if (combine != 0)
				value |= 128;

			if (++n == 8) {
				*dest++ = value;
				n = 0;
				value = 0;
			} else {
				value >>= 1;
			}
		}
	}
}
