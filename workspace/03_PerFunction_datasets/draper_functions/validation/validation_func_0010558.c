archive_write_zip_finish_entry(struct archive_write *a)
{

	int ret;
	struct zip *zip = a->format_data;
	struct zip_data_descriptor *d = &zip->data_descriptor;
	struct zip_file_header_link *l = zip->central_directory_end;
#if HAVE_ZLIB_H
	size_t reminder;
#endif

	switch(l->compression) {
	case COMPRESSION_STORE:
		break;
#if HAVE_ZLIB_H
	case COMPRESSION_DEFLATE:
		for (;;) {
			ret = deflate(&zip->stream, Z_FINISH);
			if (ret == Z_STREAM_ERROR)
				return (ARCHIVE_FATAL);
			reminder = zip->len_buf - zip->stream.avail_out;
			ret = __archive_write_output(a, zip->buf, reminder);
			if (ret != ARCHIVE_OK)
				return (ret);
			l->compressed_size += reminder;
			zip->written_bytes += reminder;
			zip->stream.next_out = zip->buf;
			if (zip->stream.avail_out != 0)
				break;
			zip->stream.avail_out = zip->len_buf;
		}
		deflateEnd(&zip->stream);
		break;
#endif
	}

	archive_le32enc(&d->crc32, l->crc32);
	archive_le32enc(&d->compressed_size, l->compressed_size);
	ret = __archive_write_output(a, d, sizeof(*d));
	if (ret != ARCHIVE_OK)
		return (ARCHIVE_FATAL);
	zip->written_bytes += sizeof(*d);
	return (ARCHIVE_OK);
}
