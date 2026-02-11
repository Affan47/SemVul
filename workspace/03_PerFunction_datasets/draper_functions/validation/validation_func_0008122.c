cli_hashfile(const char *filename, int type)
{
	FILE *fs;
	char *hashstr;


    if((fs = fopen(filename, "rb")) == NULL) {
	cli_errmsg("cli_hashfile(): Can't open file %s\n", filename);
	return NULL;
    }

    hashstr = cli_hashstream(fs, NULL, type);

    fclose(fs);
    return hashstr;
}
