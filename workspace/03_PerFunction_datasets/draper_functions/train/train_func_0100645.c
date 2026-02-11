retrieve
	(
	uint32 index,
	std::size_t& len
	)
{
	char *buffer;
	if (index >= num_segments)
		throw exult_exception("objnum too large in read_object()");

	file.seekg(0x80 + 8*index);
	long offset = Read4(file);
	len = Read4(file);
	if (!len)
		throw file_read_exception(filename);

	file.seekg(offset);
	buffer = new char[len];
	file.read(buffer, len);
	if( !file.good() )
		throw file_read_exception(filename);

	return buffer;
}
