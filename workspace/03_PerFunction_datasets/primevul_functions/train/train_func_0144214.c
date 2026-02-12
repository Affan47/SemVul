is_subdir(const char *subdir, const char *dir)
{
	size_t dirlen = strlen(dir);
	size_t subdirlen = strlen(subdir);


	if (subdirlen < dirlen)
		return false;

	if (strncmp(subdir, dir, dirlen) != 0)
		return false;


	if (dirlen > 0 && dir[dirlen - 1] == '/')
		return true;


	if (subdir[dirlen] == '/' && dirlen > 0)
		return true;


	if (subdirlen == dirlen)
		return true;
	return false;
}
