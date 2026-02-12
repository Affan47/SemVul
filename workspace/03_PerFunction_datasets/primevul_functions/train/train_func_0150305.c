int isFileInDir(char *dir, char *file){
	size_t length, dirLength;
	char *fullpath = NULL;
	FILE *f = NULL;
	int foundFile = 0;

	dirLength = strlen(dir);

	if (dir[dirLength-1] == DIR_SEPARATOR) {

		dir[dirLength-1] = '\0';
		dirLength--;
	}

	length = dirLength + strlen(file) + 2;
	fullpath = malloc(length);
	if (NULL != fullpath) {
		strcpy(fullpath, dir);
		fullpath[dirLength] = DIR_SEPARATOR;
		strcpy(fullpath+dirLength+1, file);


		f = fopen(fullpath, "rb");
		if (NULL != f) {
			foundFile = 1;
			fclose(f);
		}
		free(fullpath);
	}
	return foundFile;
}
