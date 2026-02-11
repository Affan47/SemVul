internal_add_shifted(BignumInt *number,
				 unsigned n, int shift)
{
    int word = 1 + (shift / BIGNUM_INT_BITS);
    int bshift = shift % BIGNUM_INT_BITS;
    BignumDblInt addend;

    addend = (BignumDblInt)n << bshift;

    while (addend) {
	addend += number[word];
	number[word] = (BignumInt) addend & BIGNUM_INT_MASK;
	addend >>= BIGNUM_INT_BITS;
	word++;
    }
}
