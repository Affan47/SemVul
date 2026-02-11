print_hexl(blob_t *b)
{
	u_int i, j, jm, len;
	u_char *p;
	int c;

	p = b->base + b->off;
	len = b->end - b->off;

	printf("\n");

	for (i = 0; i < len; i += 0x10) {
		printf("  %04x: ", (u_int)(i + b->off));
		jm = len - i;
		jm = jm > 16 ? 16 : jm;

		for (j = 0; j < jm; j++) {
			printf((j % 2) ? "%02x " : "%02x", (u_int)p[i + j]);
		}
		for (; j < 16; j++) {
			printf((j % 2) ? "   " : "  ");
		}
		printf(" ");

		for (j = 0; j < jm; j++) {
			c = p[i + j];
			printf("%c", isprint(c) ? c : '.');
		}
		printf("\n");
	}
}
