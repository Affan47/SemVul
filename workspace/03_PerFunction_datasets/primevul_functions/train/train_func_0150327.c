truncatePath(char *inputPath) {
	char *lastOccurence = strrchr(inputPath, DIR_SEPARATOR);

	if (NULL != lastOccurence) {
		*lastOccurence = '\0';
	}
}
