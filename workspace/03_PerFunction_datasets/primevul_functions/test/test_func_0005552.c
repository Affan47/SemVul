ImageAddress (void *image, uint64_t size, uint64_t address)
{

	if (address > size)
		return NULL;


	if (UINT64_MAX - address < (uint64_t)(intptr_t)image)
		return NULL;


	return image + address;
}
