ucs2strlen(uint16_t const * const unicstr)
{
	int length = 0;


	for(length = 0; unicstr[length] != 0x0000U; length ++);
	return length;
}
