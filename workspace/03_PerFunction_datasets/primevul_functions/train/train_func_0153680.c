static int win32_prefix_length(const char *path, int len)
{
#ifndef GIT_WIN32
	GIT_UNUSED(path);
	GIT_UNUSED(len);
#else


	if (len == 2 && LOOKS_LIKE_DRIVE_PREFIX(path))
		return 2;


	if (looks_like_network_computer_name(path, len))
		return len;
#endif

	return -1;
}
