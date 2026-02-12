strhash(st_data_t arg)
{
    register const char *string = (const char *)arg;
    register st_index_t hval = FNV1_32A_INIT;


    while (*string) {

	hval ^= (unsigned int)*string++;


	hval *= FNV_32_PRIME;
    }
    return hval;
}
