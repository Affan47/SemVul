crc32_be(uint32_t crc, unsigned char const *p, int len)
{
# if CRC_BE_BITS == 8
	const uint32_t      *b =(uint32_t *)p;
	const uint32_t      *tab = crc32table_be;

# ifdef __LITTLE_ENDIAN
#  define DO_CRC(x) crc = tab[ (crc ^ (x)) & 255 ] ^ (crc>>8)
# else
#  define DO_CRC(x) crc = tab[ ((crc >> 24) ^ (x)) & 255] ^ (crc<<8)
# endif

	crc = __cpu_to_be32(crc);

	if(((long)b)&3 && len){
		do {
			uint8_t *p = (uint8_t *)b;
			DO_CRC(*p++);
			b = (uint32_t *)p;
		} while ((--len) && ((long)b)&3 );
	}
	if(len >= 4){

		int save_len = len & 3;
	        len = len >> 2;
		--b;
		do {
			crc ^= *++b;
			DO_CRC(0);
			DO_CRC(0);
			DO_CRC(0);
			DO_CRC(0);
		} while (--len);
		b++;
		len = save_len;
	}

	if(len){
		do {
			uint8_t *p = (uint8_t *)b;
			DO_CRC(*p++);
			b = (void *)p;
		} while (--len);
	}
	return __be32_to_cpu(crc);
#undef ENDIAN_SHIFT
#undef DO_CRC

# elif CRC_BE_BITS == 4
	while (len--) {
		crc ^= *p++ << 24;
		crc = (crc << 4) ^ crc32table_be[crc >> 28];
		crc = (crc << 4) ^ crc32table_be[crc >> 28];
	}
	return crc;
# elif CRC_BE_BITS == 2
	while (len--) {
		crc ^= *p++ << 24;
		crc = (crc << 2) ^ crc32table_be[crc >> 30];
		crc = (crc << 2) ^ crc32table_be[crc >> 30];
		crc = (crc << 2) ^ crc32table_be[crc >> 30];
		crc = (crc << 2) ^ crc32table_be[crc >> 30];
	}
	return crc;
# endif
}
