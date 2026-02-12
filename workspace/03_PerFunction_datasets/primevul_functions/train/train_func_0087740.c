void hash_data(unsigned char *out_hash, const unsigned char *data)
{
	unsigned char blkheader[80];


	swap32yes(blkheader, data, 80 / 4);


	gen_hash(blkheader, out_hash, 80);
}
