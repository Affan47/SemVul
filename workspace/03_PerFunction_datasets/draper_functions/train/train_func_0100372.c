ProcessFile(FILE *in, bool stripFirstComment)
{
	char s[256];
	bool striping = false;
	while (fgets(s, sizeof(s), in)) {
		if (stripFirstComment) {
			char *x = strstr(s, "/*");
			if (x) {
				striping = true;
				stripFirstComment = false;
				continue;
			}
		}
		if (striping) {
			char *x = strstr(s, "*/");
			if (x) {
				striping = false;
			}
			continue;
		}
		const char* include = "#include";
		if (memcmp(s, include, strlen(include))) {
			fputs(s, stdout);
			continue;
		}
		char *p = strchr(s, '<');
		if (p) {
			fputs(s, stdout);
			continue;
		}
		p = strchr(s, '"');
		if (! p) {
			throw "#include misses \" - start of filename";
		}
		++p;
		char *p2 = strchr(p, '"');
		if (! p2) {
			throw "#include misses \" - end of filename";
		}
		*p2 = 0;
		p2 = strrchr(p, '/');
		if (p2) {
			p = p2 + 1;
		}
		FILE *newIn = fopen(p, "rt");
		if (! newIn) {
			continue;
		}
		ProcessFile(newIn, true);
		fclose(newIn);

		unlink(p);
	}
}
