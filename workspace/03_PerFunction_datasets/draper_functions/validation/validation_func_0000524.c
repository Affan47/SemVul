count_bits(const unsigned long bitmap[],
				unsigned long limit)
{
	unsigned long i, count = 0;

	while (limit >= BITS_PER_LONG) {
		count += popcount(bitmap[0]);
		bitmap++;
		limit -= BITS_PER_LONG;
	}

	for (i = 0; i < limit; i++)
		if (test_bit(bitmap, i))
			count++;
	return count;
}
