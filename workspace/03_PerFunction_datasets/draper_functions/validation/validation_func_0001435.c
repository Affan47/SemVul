AddLsh13(unsigned long *c, const unsigned long *b, long n)
{
    unsigned long cy = 0UL, t;

    long i;

    for (i = 0; i < n; i++) {
	t = b[i];
	c[i] ^= t ^ (t << 3) ^ cy;
	cy = t >> (GF2X_WORDSIZE - 3);
    }
    return cy;
}
