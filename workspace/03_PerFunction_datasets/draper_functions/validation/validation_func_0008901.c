write_index(git_oid *oid, git_index *index, const char *base, int baselen, int entry_no, int maxentries)
{
	size_t size, offset;
	char *buffer;
	int nr, error;


	size = maxentries * 40;
	buffer = git__malloc(size);
	if (buffer == NULL)
		return GIT_ENOMEM;

	offset = 0;

	for (nr = entry_no; nr < maxentries; ++nr) {
		git_index_entry *entry = git_index_get(index, nr);

		const char *pathname = entry->path, *filename, *dirname;
		int pathlen = strlen(pathname), entrylen;

		unsigned int write_mode;
		git_oid subtree_oid;
		git_oid *write_oid;


		if (baselen >= pathlen || memcmp(base, pathname, baselen) != 0)
			break;


		filename = pathname + baselen;
		dirname = strchr(filename, '/');

		write_oid = &entry->oid;
		write_mode = entry->mode;

		if (dirname) {
			int subdir_written;

#if 0
			if (entry->mode != S_IFDIR) {
				free(buffer);
				return GIT_EOBJCORRUPTED;
			}
#endif
			subdir_written = write_index(&subtree_oid, index, pathname, dirname - pathname + 1, nr, maxentries);

			if (subdir_written < GIT_SUCCESS) {
				free(buffer);
				return subdir_written;
			}

			nr = subdir_written - 1;


			pathlen = dirname - pathname;
			write_oid = &subtree_oid;
			write_mode = S_IFDIR;
		}

		entrylen = pathlen - baselen;
		if (offset + entrylen + 32 > size) {
			size = alloc_nr(offset + entrylen + 32);
			buffer = git__realloc(buffer, size);

			if (buffer == NULL)
				return GIT_ENOMEM;
		}

		offset += write_index_entry(buffer + offset, write_mode, filename, entrylen, write_oid);
	}

	error = git_odb_write(oid, index->repository->db, buffer, offset, GIT_OBJ_TREE);
	free(buffer);

	return (error == GIT_SUCCESS) ? nr : error;
}
