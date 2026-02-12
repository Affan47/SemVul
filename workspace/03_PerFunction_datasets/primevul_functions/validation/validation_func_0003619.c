static int scan_for_signature(struct archive_read* a) {
	const uint8_t* p;
	const int chunk_size = 512;
	ssize_t i;


	while(1) {
		if(!read_ahead(a, chunk_size, &p))
			return ARCHIVE_EOF;

		for(i = 0; i < chunk_size - rar5_signature_size; i++) {
			if(memcmp(&p[i], rar5_signature,
			    rar5_signature_size) == 0) {


				(void) consume(a, i + rar5_signature_size);
				return ARCHIVE_OK;
			}
		}

		consume(a, chunk_size);
	}

	return ARCHIVE_FATAL;
}
