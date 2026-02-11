bit_shift(chunk_t chunk)
{
	size_t i;

	for (i = 0; i < chunk.len; i++)
	{
		chunk.ptr[i] <<= 1;
		if (i < chunk.len - 1 && chunk.ptr[i + 1] & 0x80)
		{
			chunk.ptr[i] |= 0x01;
		}
	}
}
