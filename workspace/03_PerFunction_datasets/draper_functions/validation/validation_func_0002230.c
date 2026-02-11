xrealloc(char *ptr, int size)
{
	char *tmp;

	if (!(tmp = realloc(ptr, size))) {
		perror("realloc");
		exit(1);
	}

	return tmp;
}
