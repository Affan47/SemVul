zip_read_data_zipx_zstd(struct archive_read *a, const void **buff,
    size_t *size, int64_t *offset)
{
	struct zip *zip = (struct zip *)(a->format->data);
	ssize_t bytes_avail = 0, in_bytes, to_consume;
	const void *compressed_buff;
	int r;
	size_t ret;
	uint64_t total_out;
	ZSTD_outBuffer out;
	ZSTD_inBuffer in;

	(void) offset;


	if(!zip->decompress_init) {
		r = zipx_zstd_init(a, zip);
		if(r != ARCHIVE_OK)
			return r;
	}


	compressed_buff = __archive_read_ahead(a, 1, &bytes_avail);
	if(bytes_avail < 0) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Truncated zstd file body");
		return (ARCHIVE_FATAL);
	}

	in_bytes = zipmin(zip->entry_bytes_remaining, bytes_avail);
	if(in_bytes < 1) {


		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Truncated zstd file body");
		return (ARCHIVE_FATAL);
	}


	in.src = compressed_buff;
	in.size = in_bytes;
	in.pos = 0;
	out = (ZSTD_outBuffer) { zip->uncompressed_buffer, zip->uncompressed_buffer_size, 0 };


	ret = ZSTD_decompressStream(zip->zstdstream, &out, &in);
	if (ZSTD_isError(ret)) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			"Error during zstd decompression: %s",
			ZSTD_getErrorName(ret));
		return (ARCHIVE_FATAL);
	}


	if (ret == 0) {
		if ((in.pos == in.size) && (out.pos < out.size)) {
			zip->end_of_entry = 1;
			ZSTD_freeDStream(zip->zstdstream);
			zip->zstdstream_valid = 0;
		}
	}


	to_consume = in.pos;
	__archive_read_consume(a, to_consume);

	total_out = out.pos;

	zip->entry_bytes_remaining -= to_consume;
	zip->entry_compressed_bytes_read += to_consume;
	zip->entry_uncompressed_bytes_read += total_out;


	*size = total_out;
	*buff = zip->uncompressed_buffer;


	r = consume_optional_marker(a, zip);
	if(r != ARCHIVE_OK)
		return r;

	return ARCHIVE_OK;
}
