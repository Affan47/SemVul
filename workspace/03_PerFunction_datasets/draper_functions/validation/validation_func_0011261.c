buffer_file_append (BufferFile *file, const char *str, size_t len)
{
	do {
		unsigned long to_write = MIN (CHUNK_PAYLOAD - file->cur->length, len);
		memcpy (file->cur->data + file->cur->length, str, to_write);
		str += to_write;
		len -= to_write;
		file->cur->length += to_write;
		if (file->cur->length >= CHUNK_PAYLOAD)
			file->cur = chunk_alloc (file->sm, file->dest);
	} while (len > 0);
}
