hash64_stable_32(const void *key, size_t n, uint64_t base)
{
	const uint32_t *k = key;
	uint32_t a,b,c;


	a = b = c = 0xdeadbeef + ((uint32_t)n*4) + (base >> 32) + base;

	while (n > 3) {
		a += k[0];
		b += k[1];
		c += k[2];
		mix(a,b,c);

		n -= 3;
		k += 3;
	}
	switch (n) {
	case 2:
		b += (uint32_t)k[1];
	case 1:
		a += (uint32_t)k[0];
 		break;
	case 0:
		return c;
	}
	final(a,b,c);
	return ((uint64_t)b << 32) | c;
}
