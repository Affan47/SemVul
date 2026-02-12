static int uncompress_file(struct archive_read* a) {
	int ret;

	while(1) {


		ret = do_uncompress_file(a);
		if(ret != ARCHIVE_RETRY)
			return ret;
	}
}
