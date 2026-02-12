static int64_t rar5_seek_data(struct archive_read *a, int64_t offset,
    int whence)
{
	(void) a;
	(void) offset;
	(void) whence;


	return ARCHIVE_FATAL;
}
