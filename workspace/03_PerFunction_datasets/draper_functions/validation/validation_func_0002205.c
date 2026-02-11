Get8bits(const unsigned char *in, int i)
{
	unsigned int x = in[(8*i)/5] << 10;
	x |= (((in[((8*i)/5)+1]) & 0x3FF) << 5);
	if ((8*i)%5 > (10-8)) x |= ((in[((8*i)/5)+2]) & 0x3FF);
	x <<= (8*i)%5;
	return (x&0x7FFF) >> (15-8);
}
