print_mmap(const char *val)
{
	unsigned int mmaps, i, found = 0;

	errno = 0;
	mmaps = strtoul(val, NULL, 16);
	if (errno) {
		printf("conversion error(%s) ", val);
		return;
	}

	if ((mmaps & 0xF) == 0) {
		printf("MAP_FILE");
		found = 1;
	}

	for (i = 0; i < MMAP_NAMES; i++) {
		if (mmaptab[i].value & mmaps) {
			if (found == 0) {
				printf("%s", mmaptab[i].name);
				found = 1;
			} else
				printf("|%s", mmaptab[i].name);
		}
	}
	putchar(' ');
}
