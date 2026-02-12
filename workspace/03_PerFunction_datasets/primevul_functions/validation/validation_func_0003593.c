static int process_head_main(struct archive_read* a, struct rar5* rar,
    struct archive_entry* entry, size_t block_flags)
{
	int ret;
	size_t extra_data_size = 0;
	size_t extra_field_size = 0;
	size_t extra_field_id = 0;
	size_t archive_flags = 0;

	enum MAIN_FLAGS {
		VOLUME = 0x0001,
		VOLUME_NUMBER = 0x0002,

		SOLID = 0x0004,
		PROTECT = 0x0008,
		LOCK = 0x0010,
	};

	enum MAIN_EXTRA {

		LOCATOR = 0x01,
	};

	(void) entry;

	if(block_flags & HFL_EXTRA_DATA) {
		if(!read_var_sized(a, &extra_data_size, NULL))
			return ARCHIVE_EOF;
	} else {
		extra_data_size = 0;
	}

	if(!read_var_sized(a, &archive_flags, NULL)) {
		return ARCHIVE_EOF;
	}

	rar->main.volume = (archive_flags & VOLUME) > 0;
	rar->main.solid = (archive_flags & SOLID) > 0;

	if(archive_flags & VOLUME_NUMBER) {
		size_t v = 0;
		if(!read_var_sized(a, &v, NULL)) {
			return ARCHIVE_EOF;
		}

		if (v > UINT_MAX) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Invalid volume number");
			return ARCHIVE_FATAL;
		}

		rar->main.vol_no = (unsigned int) v;
	} else {
		rar->main.vol_no = 0;
	}

	if(rar->vol.expected_vol_no > 0 &&
		rar->main.vol_no != rar->vol.expected_vol_no)
	{


		return ARCHIVE_EOF;
	}

	if(extra_data_size == 0) {

		return ARCHIVE_OK;
	}

	if(!read_var_sized(a, &extra_field_size, NULL)) {
		return ARCHIVE_EOF;
	}

	if(!read_var_sized(a, &extra_field_id, NULL)) {
		return ARCHIVE_EOF;
	}

	if(extra_field_size == 0) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Invalid extra field size");
		return ARCHIVE_FATAL;
	}

	switch(extra_field_id) {
		case LOCATOR:
			ret = process_main_locator_extra_block(a, rar);
			if(ret != ARCHIVE_OK) {


				return ret;
			}

			break;
		default:
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Unsupported extra type (0x%x)",
			    (int) extra_field_id);
			return ARCHIVE_FATAL;
	}

	return ARCHIVE_OK;
}
