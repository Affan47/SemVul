JVM_NativePath(char* path)
{
	char * pathIndex;
	size_t length = strlen(path);

	Trc_SC_NativePath_Entry(path);

	if (jclSeparator == '/') {
		Trc_SC_NativePath_Exit(path);
		return path;
	}


	pathIndex = path;
	while (*pathIndex != '\0') {
		if ((*pathIndex == '\\' || *pathIndex == '/') && (*pathIndex != jclSeparator))
			*pathIndex = jclSeparator;
		pathIndex++;
	}


	pathIndex = path;
	while ((*pathIndex != '\0') && (*pathIndex == jclSeparator)) {
		pathIndex++;
	}
	if ((pathIndex > path) && (length > (size_t)(pathIndex - path)) && (*(pathIndex + 1) == ':')) {

		size_t newlen = length - (pathIndex - path);
		memmove(path, pathIndex, newlen);
		path[newlen] = '\0';
	} else {
		if ((pathIndex - path > 3) && (length > (size_t)(pathIndex - path))) {

			size_t newlen = length - (pathIndex - path) + 2;
			memmove(path, pathIndex - 2, newlen);
			path[newlen] = '\0';
		}
	}

	Trc_SC_NativePath_Exit(path);
	return path;
}
