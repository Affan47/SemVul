do_writefwdump(struct ethtool_dump *dump, const char *dump_file)
{
	int err = 0;
	FILE *f;
	size_t bytes;

	f = fopen(dump_file, "wb+");

	if (!f) {
		fprintf(stderr, "Can't open file %s: %s\n",
			dump_file, strerror(errno));
		return 1;
	}
	bytes = fwrite(dump->data, 1, dump->len, f);
	if (bytes != dump->len) {
		fprintf(stderr, "Can not write all of dump data\n");
		err = 1;
	}
	if (fclose(f)) {
		fprintf(stderr, "Can't close file %s: %s\n",
			dump_file, strerror(errno));
		err = 1;
	}
	return err;
}
