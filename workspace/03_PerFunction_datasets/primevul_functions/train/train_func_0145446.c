static PHP_FUNCTION(bzcompress)
{
	char             *source;
	long              zblock_size = 0;
	long              zwork_factor = 0;
	char             *dest = NULL;
	int               error,
					  block_size  = 4,
					  work_factor = 0,
					  argc;
	int               source_len;
	unsigned int      dest_len;

	argc = ZEND_NUM_ARGS();

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|ll", &source, &source_len, &zblock_size, &zwork_factor) == FAILURE) {
		return;
	}


	dest_len   = (unsigned int) (source_len + (0.01 * source_len) + 600);


	dest = emalloc(dest_len + 1);


	if (argc > 1) {
		block_size = zblock_size;
	}

	if (argc > 2) {
		work_factor = zwork_factor;
	}

	error = BZ2_bzBuffToBuffCompress(dest, &dest_len, source, source_len, block_size, 0, work_factor);
	if (error != BZ_OK) {
		efree(dest);
		RETURN_LONG(error);
	} else {


		dest = erealloc(dest, dest_len + 1);
		dest[dest_len] = 0;
		RETURN_STRINGL(dest, dest_len, 0);
	}
}
