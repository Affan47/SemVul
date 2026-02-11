parse_file(FILE *infile)
{
	char line[MAXLINESZ];
	char * s;
	while (fgets(line, MAXLINESZ, infile)) {
		if (line[0] == '!') {
			s = line + 2;
			switch (line[1]) {
				case 'E':
					while (*s && !isspace(*s)) s++;
					*s = '\0';
					externalfunctions(line+2);
					break;
				case 'I':
					while (*s && !isspace(*s)) s++;
					*s = '\0';
					internalfunctions(line+2);
					break;
				case 'D':
					while (*s && !isspace(*s)) s++;
                                        *s = '\0';
                                        symbolsonly(line+2);
                                        break;
				case 'F':

					while (*s && !isspace(*s)) s++;
					*s++ = '\0';

					while (isspace(*s))
						s++;
					singlefunctions(line +2, s);
					break;
				default:
					defaultline(line);
			}
		}
		else {
			defaultline(line);
		}
	}
	fflush(stdout);
}
