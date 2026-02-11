_str_to_nodes(const char *num_str, char **leftover)
{
	long int num;
	char *endptr;

	num = strtol(num_str, &endptr, 10);
	if (endptr == num_str) {
		*leftover = (char *)num_str;
		return 0;
	}
	if (*endptr != '\0' && (*endptr == 'k' || *endptr == 'K')) {
		num *= 1024;
		endptr++;
	}
	if (*endptr != '\0' && (*endptr == 'm' || *endptr == 'M')) {
		num *= (1024 * 1024);
		endptr++;
	}
	*leftover = endptr;

	return (int)num;
}
