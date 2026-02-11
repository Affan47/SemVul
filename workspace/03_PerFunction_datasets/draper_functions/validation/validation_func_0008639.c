get_huffman_code(int a, uint_8 *len, uint_16 *code)
{
	int start;
	uint_32 dis;
	*len = get_huffman_len(a);

	if (a == 0)
	{
		*code = 0;
	}
	else if (a < 0)
	{
		start = -((1 << *len) - 1);
		*code = a - start;
	}
	else
	{
		*code = a;
	}
}
