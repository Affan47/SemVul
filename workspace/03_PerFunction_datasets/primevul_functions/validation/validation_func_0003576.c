static int rar5_read_data_skip(struct archive_read *a) {
	struct rar5* rar = get_context(a);

	if(rar->main.solid) {


		int ret;


		while(rar->file.bytes_remaining > 0) {


			rar->skip_mode++;


			ret = rar5_read_data(a, NULL, NULL, NULL);


			rar->skip_mode--;

			if(ret < 0 || ret == ARCHIVE_EOF) {


				return ret;
			}
		}
	} else {


		if(ARCHIVE_OK != consume(a, rar->file.bytes_remaining)) {
			return ARCHIVE_FATAL;
		}

		rar->file.bytes_remaining = 0;
	}

	return ARCHIVE_OK;
}
