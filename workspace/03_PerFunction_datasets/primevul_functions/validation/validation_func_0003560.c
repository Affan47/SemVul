static void update_crc(struct rar5* rar, const uint8_t* p, size_t to_read) {
    int verify_crc;

	if(rar->skip_mode) {
#if defined CHECK_CRC_ON_SOLID_SKIP
		verify_crc = 1;
#else
		verify_crc = 0;
#endif
	} else
		verify_crc = 1;

	if(verify_crc) {


		if(rar->file.stored_crc32 > 0) {
			rar->file.calculated_crc32 =
				crc32(rar->file.calculated_crc32, p, to_read);
		}


		if(rar->file.has_blake2 > 0) {


			(void) blake2sp_update(&rar->file.b2state, p, to_read);
		}
	}
}
