build_decoding_table()
{
	decoding_table = (char *)malloc(256);

	for (int i = 0; i < 64; i++)
		decoding_table[(unsigned char) encoding_table[i]] = i;
}
