bytewise_xor(void *_bo, const void *_bi1, const void *_bi2,
			 size_t size)
{
	u8 *bo = _bo;
	const u8 *bi1 = _bi1, *bi2 = _bi2;
	size_t itr;
	for (itr = 0; itr < size; itr++)
		bo[itr] = bi1[itr] ^ bi2[itr];
}
