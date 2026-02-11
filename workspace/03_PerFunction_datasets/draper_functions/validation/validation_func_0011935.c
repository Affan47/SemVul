FileTruncate(File file, off_t offset)
{
	int			returnCode;

	Assert(FileIsValid(file));

	DO_DB(elog(LOG, "FileTruncate %d (%s)",
			   file, VfdCache[file].fileName));

	returnCode = FileAccess(file);
	if (returnCode < 0)
		return returnCode;

	returnCode = ftruncate(VfdCache[file].fd, offset);
	return returnCode;
}
