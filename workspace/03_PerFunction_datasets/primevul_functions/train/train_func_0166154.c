static unsigned long atalk_sum_partial(const unsigned char *data,
				       int len, unsigned long sum)
{

	while (len--) {
		sum += *data;
		sum <<= 1;
		if (sum & 0x10000) {
			sum++;
			sum &= 0xffff;
		}
		data++;
	}
	return sum;
}
