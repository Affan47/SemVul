_php_stream_mmap_range(php_stream *stream, size_t offset, size_t length, php_stream_mmap_operation_t mode, size_t *mapped_len TSRMLS_DC)
{
	php_stream_mmap_range range;

	range.offset = offset;
	range.length = length;
	range.mode = mode;
	range.mapped = NULL;


	if (length > 4 * 1024 * 1024) {
		return NULL;
	}

	if (PHP_STREAM_OPTION_RETURN_OK == php_stream_set_option(stream, PHP_STREAM_OPTION_MMAP_API, PHP_STREAM_MMAP_MAP_RANGE, &range)) {
		if (mapped_len) {
			*mapped_len = range.length;
		}
		return range.mapped;
	}
	return NULL;
}
