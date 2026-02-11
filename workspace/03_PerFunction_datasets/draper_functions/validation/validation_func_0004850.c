math_memory_ring_shift_right(const byte *mem, size_t mem_size, size_t shift, byte *res, size_t res_size)
{
	if (res == NULL)
	{
		res = (byte *) mem;
	}

	if (res_size == 0)
	{
		res_size = mem_size;
	}

	math_memory_ring_shift_right_bit(mem, mem_size, shift & 0x07, res);
	math_memory_ring_shift_right_byte(res, mem_size, shift >> 3, NULL, res_size);
}
