read_entry(
	git_index_entry **out, const void *buffer, size_t buffer_size)
{
	size_t path_length, entry_size;
	const char *path_ptr;
	struct entry_short source;
	git_index_entry entry = {{0}};

	if (INDEX_FOOTER_SIZE + minimal_entry_size > buffer_size)
		return 0;


	memcpy(&source, buffer, sizeof(struct entry_short));

	entry.ctime.seconds = (git_time_t)ntohl(source.ctime.seconds);
	entry.ctime.nanoseconds = ntohl(source.ctime.nanoseconds);
	entry.mtime.seconds = (git_time_t)ntohl(source.mtime.seconds);
	entry.mtime.nanoseconds = ntohl(source.mtime.nanoseconds);
	entry.dev = ntohl(source.dev);
	entry.ino = ntohl(source.ino);
	entry.mode = ntohl(source.mode);
	entry.uid = ntohl(source.uid);
	entry.gid = ntohl(source.gid);
	entry.file_size = ntohl(source.file_size);
	git_oid_cpy(&entry.id, &source.oid);
	entry.flags = ntohs(source.flags);

	if (entry.flags & GIT_IDXENTRY_EXTENDED) {
		uint16_t flags_raw;
		size_t flags_offset;

		flags_offset = offsetof(struct entry_long, flags_extended);
		memcpy(&flags_raw, (const char *) buffer + flags_offset,
			sizeof(flags_raw));
		flags_raw = ntohs(flags_raw);

		memcpy(&entry.flags_extended, &flags_raw, sizeof(flags_raw));
		path_ptr = (const char *) buffer + offsetof(struct entry_long, path);
	} else
		path_ptr = (const char *) buffer + offsetof(struct entry_short, path);

	path_length = entry.flags & GIT_IDXENTRY_NAMEMASK;


	if (path_length == 0xFFF) {
		const char *path_end;

		path_end = memchr(path_ptr, '\0', buffer_size);
		if (path_end == NULL)
			return 0;

		path_length = path_end - path_ptr;
	}

	if (entry.flags & GIT_IDXENTRY_EXTENDED)
		entry_size = long_entry_size(path_length);
	else
		entry_size = short_entry_size(path_length);

	if (INDEX_FOOTER_SIZE + entry_size > buffer_size)
		return 0;

	entry.path = (char *)path_ptr;

	if (index_entry_dup(out, &entry) < 0)
		return 0;

	return entry_size;
}
