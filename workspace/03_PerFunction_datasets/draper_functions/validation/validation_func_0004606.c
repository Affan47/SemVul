math_memory_shift_right_bit(const byte *mem, size_t size, size_t shift, byte *res)
{
	byte high = 0;
	size_t remain = 8 - shift;

	if (res && res != mem)
	{
		const byte *mem_start = mem;

		for (mem = mem + size - 1, res = res + size - 1; mem >= mem_start; mem--, res--)
		{
			*res = *mem >> shift | high;
			high = *mem << remain;
		}
	}
	else
	{
		byte high_bak;

		for (res = (byte *) mem + size - 1; res >= mem; res--)
		{
			high_bak = *res << remain;
			*res = *res >> shift | high;
			high = high_bak;
		}
	}
}
