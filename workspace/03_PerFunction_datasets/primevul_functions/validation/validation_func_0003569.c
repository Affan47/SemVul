static int verify_checksums(struct archive_read* a) {
	int verify_crc;
	struct rar5* rar = get_context(a);


	if(!rar->skip_mode) {

		verify_crc = 1;
	} else {


#if defined CHECK_CRC_ON_SOLID_SKIP

		verify_crc = 1;
#else

		verify_crc = 0;
#endif
	}

	if(verify_crc) {


		if(rar->file.stored_crc32 > 0) {


			if(rar->file.calculated_crc32 !=
			    rar->file.stored_crc32) {


				DEBUG_CODE {
					printf("Checksum error: CRC32 "
					    "(was: %08x, expected: %08x)\n",
					    rar->file.calculated_crc32,
					    rar->file.stored_crc32);
				}

#ifndef DONT_FAIL_ON_CRC_ERROR
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_FILE_FORMAT,
				    "Checksum error: CRC32");
				return ARCHIVE_FATAL;
#endif
			} else {
				DEBUG_CODE {
					printf("Checksum OK: CRC32 "
					    "(%08x/%08x)\n",
					    rar->file.stored_crc32,
					    rar->file.calculated_crc32);
				}
			}
		}

		if(rar->file.has_blake2 > 0) {


			uint8_t b2_buf[32];
			(void) blake2sp_final(&rar->file.b2state, b2_buf, 32);

			if(memcmp(&rar->file.blake2sp, b2_buf, 32) != 0) {
#ifndef DONT_FAIL_ON_CRC_ERROR
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_FILE_FORMAT,
				    "Checksum error: BLAKE2");

				return ARCHIVE_FATAL;
#endif
			}
		}
	}


	return ARCHIVE_OK;
}
